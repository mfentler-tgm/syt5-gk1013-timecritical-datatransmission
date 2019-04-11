# Embedded Devices "Time-critical data-transmission"

## Aufgabenstellung
Die detaillierte [Aufgabenstellung](TASK.md) beschreibt die notwendigen Schritte zur Realisierung.

## Recherche

## Implementierung

### Fragestellungen für das Protokoll
+ __Was ist die Clock__  
Ist ein Timer, der festlegt in welchem Intervall der Prozessor Instruktionen ausführt. Operations/Second = Clock Speed  
+ __Was sind Interrupts__  
Unterbrechungsanforderungen -> setzt eine Flag -> Ruft die zugehörige Interrupt Service Routine auf
+ __Wie kann man Interrupts priorisieren?__  
Über Interrupt-Prioritäts-Register IP0 und IP1.
    ```bash
    MOV IP0 #100b;
    MOV IP1 #100b;
    ```
    Beim STM32 stehen für Interrupts 4 Bit zur Verfügung. Diese ganzen 4 Bit müssen auf die Preemption-Priority und Sub-Priority verteilt werden.  
      
    **Preemption-Priority**: Je niedriger die Bits desto höher die Priorität  
      
    **Sub-Priority**: Sind von 2 Interrupts die Preemption-Priority gleich, wird die Sub-Priority verglichen. Je niedriger desto höhere Priorität.  
      
    Da man insgesamt 4 bit verteilen kann gibt es 4 Gruppen:  
    |Gruppe|\|\||Preemption|Sub Priority|  
    | ------------- |:----:|:-------------:|:-----:|  
    |group0| \|\||0 bits for preemption|4 bits for sub priority|  
    |group1|\|\||1 bits for preemption|3 bits for sub priority|  
    |group2|\|\||2 bits for preemption|2 bits for sub priority|  
    |group3|\|\||3 bits for preemption|1 bits for sub priority|  
    |group4|\|\||4 bits for preemption|0 bits for sub priority|  

+ __Was ist ein SPI-Bus und wie ist dieser aufgebaut?__  
Bussystem, bestehend aus 3 Leitungen für synchrone, serielle Kommunikation.  
3 Leitungen:  
    - MOSI (MasterOut - SlaveIn)
    - MISO (MasterIn - SlaveOut)
    - SCLK (Seriell Clock): Gibt Kommunikationstakt vor.  
    
    Weiters gibt es noch die SS (SlaveSelect) Verbindung. Die kann benutzt werden um einem Slave zu signalisieren, dass jetzt eine neue Nachricht kommt oder das er jetzt selbst sprechen darf.
+ __Welche Vorteile ergeben sich bei der Verwendung eines Kommunikationsbusses?__  
1:N Verbindung (Master : n Slaves), 1:1 Verbindung (Master : Slave) auch möglich  
Synchrone Kommunkation (getimed durch SCLK)  
Vorgegebene Übertragungsrate von der Clock
+ __Welche Möglichkeiten der Beschaltung sind beim SPI-Bus möglich und wie wirkt sich die Clock darauf aus?__  
 1:1, 1:N  
Die Clock dient der Synchronisation der Datenkommunikation und wird an alle Geräte gesendet 1:N, auch wenn diese gerade nicht vom Master angesprochen werden.  

+ __Wie werden zeitkritische Anwendungen (real-time) eingeteilt?__  
    - **Hard**: Wird die Deadline überschritten kommt es zu einem kompletten Systemausfall  
    - **Mittel**: Deadline Überschreitungen werden toleriert, aber das Ergebnis ist nach Überschreitung unbrauchbar  
    - **Weich**: Deadlines sind nur Richtlinien, Quality of Service sinkt nach Überschreitung jedoch

+ __Was ist ein Watchdog__  
Ein Timer, der das Programm nach Ablauf des Timers neu startet. Deswegen muss der Watchdog vom Programm immer wieder zurückgesetzt werden.
+ __Wie kommt ein Watchdog bei zeitkritischen Anwendungen zum Einsatz?__  
Sollte es Fehler im Programm geben und das Programm kommt nicht bis zu dem Schritt, wo der Timer wieder zurückgesetzt wird, dann startet der Watchdog das Programm neu.
+ __Was sind Real-Time Operating-Systems (RTOS) und wie kann man diese auf Mikrokontrollern einsetzen?__  
Betriebsysteme, die Multithreaded arbeiten und die Threads nach deren Deadline priorisiert. Sollte ein Thread näher zur Deadline kommen -> diesem Thread werden mehr Ressourcen zugewiesen.  
Sheduler des OS orientiert sich nach der Thread-Deadline und priorisiert die Threads danach. (In Windows wird Priorität auf die Responsibility gelegt)

## Quellen
[1] [http://micromouseusa.com/?p=279](http://micromouseusa.com/?p=279)  
[2] [http://www.mikrocontroller-programmierung.de/](http://www.mikrocontroller-programmierung.de/)

