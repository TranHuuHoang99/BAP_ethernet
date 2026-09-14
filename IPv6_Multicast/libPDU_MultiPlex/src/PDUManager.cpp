#include "PDUManager.h"
#include <algorithm>
#include "logging.h"

/**
 * @brief Construct a new PDU Manager:: PDU Manager object
 * 
 * This constructor initializes the PDUManager with the specified multicast group address,
 * local port, remote port, VLAN priority, and an optional local IP address to bind.
 * 
 * @param group_addr Multicast group address
 * @param local_port Local port to bind
 * @param remote_port Remote port to send to
 * @param vlan_pro VLAN priority
 * @param local_ip Optional local IP address to bind
 * 
 * @note If local_ip is empty, the socket will bind to all available interfaces
 */
PDUManager::PDUManager(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, uint32_t vlan_pro, const std::string& local_ip)
    : socket_(group_addr, local_port, remote_port, vlan_pro) {
    if (!local_ip.empty()) socket_.setLocalAddress(local_ip);
    socket_.setReceiveCallback(std::bind(&PDUManager::onRecv, this, std::placeholders::_1));
    LOGI("PDUManager onRecv callback registered before socket start");
}

/**
 * @brief Construct a new PDU Manager:: PDU Manager object with custom socket wrapper
 * 
 * This constructor initializes the PDUManager with the specified multicast group address,
 * local port, remote port, a custom socket wrapper, VLAN priority, and an optional local IP address to bind.
 * 
 * @param group_addr Multicast group address
 * @param local_port Local port to bind
 * @param remote_port Remote port to send to
 * @param socket_wrapper Custom socket wrapper for socket operations
 * @param vlan_pro VLAN priority
 * @param local_ip Optional local IP address to bind
 * 
 * @note If local_ip is empty, the socket will bind to all available interfaces
 */
PDUManager::PDUManager(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, std::shared_ptr<ISocketWrapper> socket_wrapper, uint32_t vlan_pro, const std::string& local_ip)
    : socket_(group_addr, local_port, remote_port, socket_wrapper) {
    if (!local_ip.empty()) socket_.setLocalAddress(local_ip);
    socket_.setReceiveCallback(std::bind(&PDUManager::onRecv, this, std::placeholders::_1));
    LOGI("PDUManager onRecv callback registered before socket start");
}

/**
 * @brief Start the multicast group communication
 * 
 * This method starts the multicast socket to begin sending and receiving PDUs.
 * 
 * @return true if the multicast group started successfully, false otherwise
 */
bool PDUManager::startMulticast() {
    bool ok = socket_.start();
    running_ = ok;
    LOGI("PDUManager startMulticast group start result=%d", ok ? 1 : 0);
    return ok;
}

/**
 * @brief Stop the multicast group communication
 *
 * This method stops the multicast socket, terminating sending and receiving PDUs.
 */
void PDUManager::stopMulticast() {
    LOGI("PDUManager stopMulticast");
    socket_.stop();
    running_ = false;
}

/**
 * @brief Send a batch of PDUs immediately
 * 
 * This method sends a vector of PDUs directly through the multicast socket.
 * 
 * @param pdus Vector of PDUs to be sent
 */
void PDUManager::sendPDU(const std::vector<PDU>& pdus) {
    LOGD("PDUManager direct send batch size=%zu", pdus.size());
    socket_.sendPDUs(pdus);
}

/**
 * @brief Insert a PDU into the cache for future sending
 * 
 * This method adds a PDU to the internal cache and marks it for sending.
 * 
 * @param pdu The PDU to be inserted into the cache
 */
void PDUManager::insertPDU(const PDU& pdu) {
    std::lock_guard<std::mutex> lk(cache_mutex_);
    pdus_cache_[pdu.message_id] = pdu;
    pending_send_ids_.insert(pdu.message_id);
    LOGD("PDUManager insert id=%u len=%u cacheSize=%zu", pdu.message_id, pdu.length, pdus_cache_.size());
}


#if UNIT_TEST
/**
 * @brief (Testing only) Removes a specific PDU from cache.
 *
 * This method is intended for unit testing purposes to manipulate
 * 
 * @param msg_id The ID of the message to remove.
 */
void PDUManager::deletepduscache(uint32_t msg_id) {
    std::lock_guard<std::mutex> lk(cache_mutex_);
    pdus_cache_.erase(msg_id);
}

#endif

/**
 * @brief Send all PDUs currently stored in the cache
 * 
 * This method retrieves all PDUs marked for sending from the cache,
 * sends them through the multicast socket, and then removes them from the cache.
 */
void PDUManager::sendPDU() {
    // Immediately send all PDUs currently stored in the cache
    std::vector<PDU> pdus;
    std::vector<uint32_t> sent_ids;
    {
        std::lock_guard<std::mutex> lk(cache_mutex_);
        pdus.reserve(pending_send_ids_.size());
        sent_ids.reserve(pending_send_ids_.size());
        for (uint32_t id : pending_send_ids_) {
            auto it = pdus_cache_.find(id);
            if (it != pdus_cache_.end()) {
                pdus.push_back(it->second);
                sent_ids.push_back(id);
            }
        }
    }
    LOGD("PDUManager sendPDU pendingBatch size=%zu", pdus.size());
    if (pdus.empty()) {
        return;
    }
    sendPDU(pdus);
    // Remove only the PDUs that were just transmitted from the cache
    {
        std::lock_guard<std::mutex> lk(cache_mutex_);
        for (uint32_t id : sent_ids) {
            pdus_cache_.erase(id);
        }
        pending_send_ids_.clear();
        LOGD("PDUManager cleared %zu pending PDUs after send cacheSize=%zu", sent_ids.size(), pdus_cache_.size());
    }
}

/**
 * @brief Retrieve the current PDU for a given message ID
 * 
 * This method looks up the cache for a PDU with the specified message ID.
 * 
 * @param msg_id The message ID of the PDU to retrieve
 * @return std::optional<PDU> The PDU if found, or std::nullopt if not found
 */
std::optional<PDU> PDUManager::getCurrentPDU(uint32_t msg_id) {
    std::lock_guard<std::mutex> lk(cache_mutex_);
    auto it = pdus_cache_.find(msg_id);
    if (it != pdus_cache_.end()) return it->second;
    return std::nullopt;
}

/**
 * @brief Register a notifier callback for a specific message ID
 * 
 * This method allows clients to register a callback function that will be invoked
 * whenever a PDU with the specified message ID is received.
 * 
 * @param msg_id The message ID to register the notifier for
 * @param cb The callback function to be invoked on receiving the PDU
 */
void PDUManager::registerNotifier(uint32_t msg_id, Notifier cb) {
    std::lock_guard<std::mutex> lk(notifier_mutex_);
    notifiers_[msg_id].push_back(cb);
    LOGD("PDUManager registerNotifier id=%u totalNotifiers=%zu", msg_id, notifiers_[msg_id].size());
}

/**
 * @brief Callback method invoked when PDUs are received
 * 
 * This method processes a batch of received PDUs, updates the cache,
 * and invokes any registered notifier callbacks for each PDU.
 * 
 * @param pdus Vector of received PDUs
 */
void PDUManager::onRecv(const std::vector<PDU>& pdus) {
    LOGD("PDUManager onRecv batch size=%zu", pdus.size());
    for (const auto& pdu : pdus) {
        {
            std::lock_guard<std::mutex> lk(cache_mutex_);
            pdus_cache_[pdu.message_id] = pdu;
        }
        std::vector<Notifier> cbs;
        {
            std::lock_guard<std::mutex> lk(notifier_mutex_);
            auto it = notifiers_.find(pdu.message_id);
            if (it != notifiers_.end()) cbs = it->second;
        }
        for (auto& cb : cbs) {
            cb(pdu);
        }
    }
    LOGD("PDUManager onRecv processed batch end");
}
