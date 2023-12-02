TCP Socket Programimi me C++

Përmbledhje

Ky projekt paraqet një sistem të thjeshtë komunikimi me soketa TCP midis një serveri dhe disa klientëve duke përdorur gjuhën programuese C++. Serveri është në gjendje të trajtojë lidhje të shumta klientësh dhe të kryejë operacione të ndryshme bazuar në kërkesat e klientëve.


Kërkesat për funksionalitet 
 
Duhet të jenë te instaluara:
* Kompilues C++
* Libraria Winsock (për Windows)


Privilegjet e Klientit

* Shkruaj, Lexo, Ekzekuto:Klienti i parë ka privilegje shkrimi, leximi dhe ekzekutimi.
* Vetëm Lexo: Klientët e tjerë kanë vetëm privilegje leximi.


Komandat e Serverit

* Mesazh Tekstual: Serveri përgjigjet tek mesazhet tekstuale nga klientët.
* Lexo file: Klientët mund të kërkojnë të lexojnë përmbajtjen e një file në server.  file r: emri_file.txt  
* Shkruaj file: Klientët me privilegje write mund të kërkojnë të shkruajnë përmbajtjen në një file në server.  file w: emri_file.txt përmbajtja


Shënime

* Përditësoni adresën IP të serverit në file client.cpp për të përputhur me adresën IP të serverit tuaj.  


Punuan: <br>
[Dëshira Randobrava](https://github.com/d3shira) <br>
[Diart Maraj](https://github.com/diartmaraj) <br>
[Ema Zeqiri](https://github.com/emazech)
[Era Maliqi](https://github.com/eramaliqi)


