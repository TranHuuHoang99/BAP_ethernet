#ifndef __PDUMANAGER_H_
#define __PDUMANAGER_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>
#include <optional>
#include <mutex>
#include "pdu.h"
#include "MulticastSocket.h"

struct PDUManagerTestFriend;

class PDUManager {
public:
    using Notifier = std::function<void(const PDU&)>;

    PDUManager(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, uint32_t vlan_pro = 0, const std::string& local_ip = "");
    // Dependency injection constructor for testing
    PDUManager(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, std::shared_ptr<ISocketWrapper> socket_wrapper, uint32_t vlan_pro = 0, const std::string& local_ip = "");

    bool startMulticast();
    void stopMulticast();
    bool isMulticastRunning() const { return running_; }
    void sendPDU(const std::vector<PDU>& pdus);
    void insertPDU(const PDU& pdu);
    void sendPDU();
    std::optional<PDU> getCurrentPDU(uint32_t msg_id);
    void registerNotifier(uint32_t msg_id, Notifier cb);
    #ifdef UNIT_TEST
    void deletepduscache(uint32_t msg_id);
    #endif

private:
    void onRecv(const std::vector<PDU>& pdus);

private:
    std::unordered_map<uint32_t, PDU> pdus_cache_;
    std::unordered_set<uint32_t> pending_send_ids_;
    std::unordered_map<uint32_t, std::vector<Notifier>> notifiers_;
    MulticastSocket socket_;
    std::mutex cache_mutex_;
    std::mutex notifier_mutex_;
    bool running_ = false;

    friend struct PDUManagerTestFriend;
};

#endif // __PDUMANAGER_H_
