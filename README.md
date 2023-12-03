# TCP Socket Programimi me C++

Lënda: Rrjeta Kompjuterike 


# Përmbledhje

Ky projekt paraqet një sistem të thjeshtë komunikimi me soketa TCP midis një serveri dhe disa klientëve duke përdorur gjuhën programuese C++. Serveri është në gjendje të trajtojë lidhje të shumta klientësh nga një numër pajisjesh dhe të kryejë operacione të ndryshme bazuar në kërkesat e klientëve.


# Kërkesat për funksionalitet 
 
Duhet të jenë te instaluara:

* Kompilues C++
* Libraria Winsock (për Windows)


# Komandat e Klientit

* Klienti i parë ka privilegje shkrimi, leximi dhe ekzekutimi (append file dhe delete file).
* Klientët e tjerë kanë vetëm privilegje leximi.


# Komandat e Serverit

* Mesazh Tekstual: Serveri përgjigjet tek mesazhet tekstuale nga klientët.


# Privilegjet e Klientëve
  
Klientët me privilegje mund të:
   *  write(): shkruajnë përmbajtjen në një file në server.  file w: emri_file.txt përmbajtja
   *  read(): lexojnë përmbajtjen në një file: file r: emri_file.txt
   *  exec(): shtojnë të dhëna në file ekzistues: file a: emri_file.txt përmbajtja shtesë
   *  exec(): fshijnë files ekzistues:file d: emri_file.txt

 Klientët e zakonshëm mund të kërkojnë të lexojnë përmbajtjen e një file në server:  file r: emri_file.txt


# Libraritë

Në këtë kod C++ kemi implementuar përdorimin e disa librarive të ndryshme që kemi cekur në vijim:

Në anën e klientit: 
  * #include < iostream >
  * #include < winsock2.h >

Në anën e serverit:
  * #include < WinSock2.h >
  * #include < string >
  * #include < iostream >
  * #include < fstream >
  * #include < unordered_set >
  * #include < thread >


# Punuan: <br>
[Dëshira Randobrava](https://github.com/d3shira) <br>
[Diart Maraj](https://github.com/diartmaraj) <br>
[Ema Zeqiri](https://github.com/emazech) <br>
[Era Maliqi](https://github.com/eramaliqi)


