# Tema1_LFA

Un algoritm care are ca input un <placeholder> si o lista de string-uri. Acesta afiseaza DA/NU pentru fiecare cuvant si un traseu/drum in automat (cel putin pentru primul), daca este acceptat sau nu. Unde <placeholder> este un automat finit nedeterminist cu lambda tranzitii (lambda-NFA).
  
Observatii:
  - Daca exista mai multe trasee posibile, se va afisa doar primul gasit
  - Datele de intrare contin pe prima linie n (numarul de noduri) si m (numarul de tranzitii). 
  Pe urmatoarele m linii sunt descrise tranzitiile din fiecare automat. 
  Pe linia m + 2 se afla indicele starii initiale. 
  Pe linia m + 3 se afla un numar nf (numarul de stari finale) urmat de indicii starilor finale respective, separate prin spatiu. 
  Linia m+ 4 contine ni, numarul de string-uri de input, iar pe urmatoarele ni linii, string-urile respective.
  - Datele de iesire, pentru fiecare string: contin DA, daca cuvantul este acceptat si un traseu posibil, respectiv NU, in caz contrar.

 
<img width="411" alt="Captură de ecran din 2022-04-03 la 01 30 05" src="https://user-images.githubusercontent.com/94484148/161403398-d8045259-f6b6-4e27-b25c-5086535d049a.png">
