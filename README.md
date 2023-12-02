TCP Socket Programimi me C++

Përmbledhje

Ky projekt paraqet një sistem të thjeshtë komunikimi me soketa TCP midis një serveri dhe disa klientëve duke përdorur gjuhën programuese C++. Serveri është në gjendje të trajtojë lidhje të shumta klientësh nga një numër pajijsesh dhe të kryejë operacione të ndryshme bazuar në kërkesat e klientëve.


Kërkesat për funksionalitet 
 
Duhet të jenë te instaluara:
* Kompilues C++
* Libraria Winsock (për Windows)

* Klienti i parë ka privilegje shkrimi, leximi dhe ekzekutimi (append file dhe delete file).
* Klientët e tjerë kanë vetëm privilegje leximi.

Komandat e Serverit

* Mesazh Tekstual: Serveri përgjigjet tek mesazhet tekstuale nga klientët.

Privilegjet e Klientit
  
* Klientët me privilegje mund të:
*  write(): shkruajnë përmbajtjen në një file në server.  file w: emri_file.txt përmbajtja
*  read(): lexojnë përmbajtjen në një file: file r: emri_file.txt përmbajtja
*  exec(): shtojnë të dhëna në file ekzistues: file a: emri_file.txt përmbajtja shtesë
*  exec(): fshijnë file-s ekzistues:file d: emri_file.txt

*  * Klientët e zakonshëm mund të kërkojnë të lexojnë përmbajtjen e një file në server:  file r: emri_file.txt



Punuan: <br>
[Dëshira Randobrava](https://github.com/d3shira) <br>
[Diart Maraj](https://github.com/diartmaraj) <br>
[Ema Zeqiri](https://github.com/emazech) <br>
[Era Maliqi](https://github.com/eramaliqi)


