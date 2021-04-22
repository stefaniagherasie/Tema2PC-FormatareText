# Tema2PC-FormatareText
[Tema1 Programarea Calculatoarelor (2018-2019, seria CB)] 

Programul simuleaza formatarea unui plain text prin aplicarea diferitelor operatii (Center, Justify, Align, Wrap , List). <br>
Enunt: https://ocw.cs.pub.ro/courses/programare/teme_2018/tema2_2018_cbd


#### RULARE
> ```shell
>    make run ARGS='"W 50, C 0 0, L1" in.txt out.txt'
> ```
>  - primul argument reprezintă un șir de caractere care indică operațiile (separate prin virgulă)
>  - al doilea argument este calea către fișierul de intrare
>  - al treilea argument este numele fișierului formatat care va fi generat

#### ORGANIZARE
- WRAP text    (**W max_line_length**) <br>
    Operația wrap adaugă și elimină caractere newline din text astfel încât textul să se încadreze în max_line_length (să aibă lungimea - în octeți - mai mică sau egală), fără a permite linii prea scurte (în afara ultimei linii dintr-un paragraf) și fără a trunchia cuvintele.

- CENTER Text   (**C [start_line [end_line]]**) <br>
    Operația center folosește ca referință cea mai lungă linie din fișier (fără trailing whitespace) și adaugă spații la începutul liniilor care sunt mai scurte pentru a le centra.
  
- ALIGN LEFT    (**L [start_line [end_line]]**) <br>
    Operația align left aliniază liniile precizate la marginea din stânga.

- ALIGN RIGHT   (**R [start_line [end_line]]**) <br>
    Operația align right aliniază liniile precizate la marginea din dreapta.

- JUSTIFY       (**J [start_line [end_line]]**)  <br>
    Operația justify folosește ca referință cea mai lungă linie din fișier și distribuie în mod echilibrat spații în interiorul liniilor mai scurte pentru ca acestea să ajungă la aceeași lungime și să fie aliniate atât la dreapta, cât și la stânga.
