Diese Datei enthaelt die CAN Spezifika der hier hinterlegten Dateien:

Dateiname                                    VARIABLE_DLC          BAP_BCL_CanRxPreCopy         BAP_BCL_CanRxPreCopy              zyklische
                                                                mit CanHandle wird benutzt  mit CanRxInfoStructPtr wird benutzt   Kommunikation     CanRxConfirmation
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bap_bclcan_vector_hcs12.c                        X                          X

bap_bclcan_vector_st10.c                         X                                                             X

bap_bclcan_vector_struct.c                       X                                                             X

bap_bclcan_vector_portable_novardlc.c            0                                                                                                            x 
                                        nur moeglich, wenn                                                                                         Polling statt Interrupt-
                                        DLC-Check des CAN-Treibers                                                                                 Betrieb ist moeglich
                                        deaktiviert -> 
                                        geringe Robustheit ->
                                        Fehlverhalten moeglich ->
                                        ist i.d.R. verboten


