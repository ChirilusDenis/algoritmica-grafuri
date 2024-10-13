# 1. Numarare
        Se citesc cele doua graphuri sub forma a 2-a array-uri de liste de adiacenta.
        Pentru determinarea numarului de lanturi elemntare comune celor doua grafuri, se parcurge primul graf cu un DFS modificat pornind din nodul 1. La fiecare nod al primului graf, se continua parcurgerea lui doar prin vecinii sai comuni cu vecinii aceluiasi nod din graful 2.
        Cand gasim nodul N, DFS va returna 1 pentru a semnala gasirea unui drum de la 1 pana la N.
        Fiecare nod parcurs de DFS va returna numarul de drumuri de la acesta pana la N, numarul de drumuri fiind egal cu suma numarului de drumuri de la vecinii sai pana la N.
        In final, DFS va returna numarul de drumuri de la nodul 1 la nodul N.
Complexitate citire: O(m)\
Complexitate verificare daca o muchie apartine grafului 2 : O(m/n)\
Complexiate finala: O(m * m / n)

# 2. Trenuri
        Toate orasele sunt stocate intr-un map, alaturi de indexul asociat lor. Orasele primesc indexuri de la 1 la numarul de orase, in ordinea in care au fost citite.
        Pentru gasirea drumului de lungime maxima, se foloseste din nou un DFS modificat, incepand din nodul dat ca sursa. Cand nodul destinatie este gasit, DFS returneaza 1. Distanta din fiecare nod pana la nodul destinatie este maximul dintre distanta maxima a vecinilor + 1.
        La terminarea DFS-ului, se va returna distanta maxima dintre nodul sursa si nodul destinatie.

Complexitate gasire/ assignare index al orasului (hashmap): O(1)\
Complexitate citire: O(m * 1)\
Complexitate finala: O(m) (DFS) + C_citire = O(m)
# 3. Drumuri
        Pentru a calcula distanta minima dintre cele 3 noduri, se va lua minimul drintre suma drumurilor x->k, y->k si k->z, unde k este un nod intermediar.
        Graful este memorat ca un array de liste de perechi, unde primul element al perechii este indexul vecinului si al doilea este costul de a ajunge la el de la parinte. 
        Folosind Dijsktra cu priority queue, se afla distantele minime de la x la toate k si de la y la toate k.
        Pe un graf cu muchii orientate invers si cu acelasi cost, se gasesc distantele minime de la z la toate k.
        Apoi, trecand prin toate nodurile ca noduri intermediare, se calculeaza minimul dintre suma distantelor x->k, y->k si k->z.

Complexitate Dijsktra: O(m logn)\
Complexitate creare graf si graf invers: O(m)\
Complexitate gasire minim dintre suma drumurilor: O(n)\
Complexitate finala :O(m) + 3 * O(m long n) + O(n) = O(m log n)

# 4. Scandal
        Pentru rezolvarea problemei se construieste un graf cu 2n noduri:
        a. noduri i de la 1 la n, care semnifica ca prietenul i este invitat
        b. noduri i de la n+1 la 2n,  vare semnifica ca prietenul i-n nu este invitat
        

        In acest graf se construiesc muchii dupa implicatiile celor 4 reguli:
        * daca putin unul dintre x si y vine implica:
                (x  neinvitat -> y) invitat si (y neinvitat ->  x invitat)
        * daca x nu vine, atunci nici y nu vine implica:
                (x neinvitat -> y neinvitat) si (y invitat -> x invitat)
        * daca y nu vine, x nu vine implica:
                (y neinvitat -> x neinvitat) si (x invitat -> y invitat)
        * daca nu pot veni ambii implica:
                (x invitat -> y neinvitat) si (y invitat -> x neinvitat)

        Pe acest graf se gasesc toate componentele tari conexe folosind Tarjan, si pe fiecare nod dintr-o componenta tare conexa, daca acesta nu a fost invitat precedent, invita-l si nu il invita pe opusul sau.
        Obs. A invita un nod ce semnifica absenta unui prieten este echivalent cu a nu invita acel prieten.

Complexitate citire: O(m), m = numar de muchii/reguli\
Complexitate tarjan: O(2 * n + m), n = numar de priteni\
Complexitate afisare: O(n)\
Complexitate finala: O(n + m)
