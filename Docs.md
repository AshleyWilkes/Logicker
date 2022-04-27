# Grid

Grid je datová struktura Logickera. Odpovídá obrazci, v němž se úloha na papíře řeší. Obrazce různých úloh jsou velmi různorodé, design Gridu se snaží poskytnout jednotný interface pro načítání a přístup k datům úloh.

Staticky (compile-time) je Grid stromová struktura, kde uzel označuje datový typ (číslo, písmeno, prázdné/plné kolečko atd.) a kde hrana mezi dvěma uzly znamená, že hodnotě počátečního datového typu (např. souřadnice políčka ve čtvercovém gridu) se přiřazuje hodnota koncového datového typu (např. číslo 1-9, které patří do políčka o daných souřadnicích). Hrany Gridu se označují názvem Slot. Stromová struktura Gridu je popsaná jako c++ typ, který lze instanciovat a získat tak run-time instanci Gridu s příslušnou strukturou.

Dynamicky (run-time) tvoří Grid std::mapy (jedna pro každý Slot), do nichž se zapisují a z nichž se čtou příslušné vztahy mezi hodnotami.

##Specifikace statické struktury Gridu
Uzel v Gridu je popsán dvěma vlastnostmi: svým Id a svou implementací. Jako Id slouží libovolný c++ typ (např. jakákoli class). Doporučuje se používat třídy z namespace Grid::SlotId. Implementace uzlu je třída, splňující API popsané níže.

Vytvoření nového Gridu se provede templatou

    Grid<Id, Topology = None>

Tato instancializace vytvoří nový Grid s jediným uzlem, označeným Id.

Sloty se přídávají pomocí templaty

    addSlot<ParentId, Id, Type>

Ta vyžaduje, aby ParentId už byl v Gridu přítomen a naopak Id nebylo v Gridu přítomno. Jsou-li tyto požadavky splněny, addSlot představuje Grid, jaký vznikne z původního Gridu doplněním nového Slotu<Id, Type>.

//Zde Type představuje specifikaci množiny hodnot, jež lze do daného Slotu zapsat. ??Run-time instance Gridu musí být schopna pro každý klíč každého Slotu určit, jaké values jsou možné?? Představme si např. Tapu, některá pole obsahují Black/White, jiná vector<Count>. Je tedy zjevně třeba umět udělat union typů, chci říct použít std::variant. 
//Představme si dále Sudoku s překvapením, tj. nevyplňujou se čísla jako dycky, ale písmena z nějaké množiny. Zde vidíme, že Type má v některých případech být parametrem celé úlohy; není-li zrovna v případě Sudoku Type zadán, pak se použije default, což v daném případě je Count<1, Size>. Takovýto default nemůže být plně inicializován při kompilaci, neboť hodnota Size není dána dřív než za běhu a nemusí být ani pro např. dvě zároveň existující instance Sudoku stejná.
//Je tedy třeba nějak compile time zapsat, že se má hodnota určit až v runtime, tj. zároveň s inicializací příslušného Slotu, viz níže. Nejjednodušeji asi tak, že se vždy určí až v runtime, jen pro některé případy to shodou okolností bude vždy stejný výsledek, jejž by bylo možno znát už při kompilaci. Tedy např. Black/White při běhu určí, že hodnoty jsou Black/White; Count<1, Size> při běhu určí, že hodnoty jsou třeba 1..9

##API Slotu
Slot je jednoduchý wrapper nad std::map<Key, std::optional<Value>> anebo std::map<Key, std::vector<std::optional<Value>>>. Má static constexpr proměnnou OneTo s možnými hodnotami One a Many; první odpovídá mapě [Key, Value], druhá mapě [Key, vector<Value>]. API kopíruje API of std::map. 

##Inicializace Slotu
Krom API of std::map navíc existuje metoda 

    bool Slot::tryInput(Grid&, GridDataPresenter)

, která slouží k inicializaci. Tato metoda se pokusí inicializovat co nejvíce values daného Slotu, pro každý klíč jednu. Vrátí true, pokud se podařilo inicializovat alespoň jednu value.

Postup je, že si metoda zkusí vyndat z GridDataPresentera SlotDataPresentera, případně použije defaultního (pokud GridDataPresenter žádného neobsahuje, ale defaultní je k dispozici), a volá na něm metodu 

    virtual std::optional<Value> SlotDataPresenter::provideValue<Value>(Grid&, Key)

Tato metoda má tedy k dispozici kompletní(??) data, která může potřebovat: SlotDataPresentera, který může znát input stream nebo whatever, typ Value, kompletní so-far-inicializovaný Grid a klíč, k němuž hodnota patří. Na základě těchto informací vytvoří (anebo ne) instanci typu Value správně naplněnou hodnotami.

##API instance Gridu
Připouštím sice, že můžou být užitečné nějaké convenience metody, ale Grid jako takový je pouze compile time mapa, umožňující retrievnout instanci Slotu na základě identifikátoru ValueId tohoto Slotu. Jinak řečeno jedna metoda, která nemá runtime parametry, je templatovaná na ValueId a vrací vhodnou instanci Slot.


#Direction vs Area
Hodnoty lze přiřazovat nejen jednotlivým políčkům (Center, Border, Corner), ale také skupinám těchto (typicky Centerů). Typicky se jedná o Directions (v Rectanglu jsou to Rows a Columns) a Areas (v zadání určeným skupinám Centerů). Directions jsou dané Topologií; Areas jsou zadány ad hoc. Directions jsou tedy vždy dané, Areas hypoteticky nemusí být v zadání specifikovány a jejich obsah hypoteticky může být součástí řešení (solving) úlohy. Pro Areas tedy platí, že AreaValue je daná pro skupinu políček, jejichž slot AreaId splňuje nějaký predikát (protože políčko může být součástí několik Areas), kurva fix.
Jinak: při validityChecku jsem schopen pro určité AreaId zjistit, která políčka do něj patří a která ne; pro patřící skupinu políček pak musí platit nějaká podmínka.
Neboli políčko má mít Slot Regions, kam spadnou Directions i Areas, ten je pak mapou RegionId -> bool. Tedy FieldId -> ( RegionId -> bool ). Jak se to rýmuje? Rýmuje se to dobře, pokud smí existovat Value typu Mapa. /*Už se počítá s Value typu Set a Vector, do toho by se to mohlo vejít. Kdyby se Fieldu dal Slot<Regions, Set<Index>> obsahující všechny relevantní DirectionId a AreaId, mělo by to stačit. Pokud by ovšem daný Index nebyl jen Index, ale kombinace (DirectionId nebo NamedAreaId, tj. NamedRegionId) + Index. Čili tady furt ochcávám to, že mi nestačí Set, ale potřebuju i Map. Což by se mohlo šiknout i pro případy, kdy Direction givens jsou dané pro oba směry (zprava doleva i zleva doprava). Obtíž je v tom, aby ta Mapa připouštěla klíče více než jednoho typu. Anebo mít Set<Map<xx>>.*/

#Value
Ok, co je teda Value? Identifikoval jsem 4 simple Values: číslo, písmeno, enum (e.g. named bool), FieldId. Dále mám skupinové typy pair, set, sequence a map. A kombinované typy or a and.
Všechny jsou snad teoreticky zvládnuté, jen ta mapa. Klíče v mapě musí být values, ale to se zdá být jako problém, který by řešila nová simple Value RegionId, která by uměla hodnoty jako [East, 1]. Takže to není simple Value, ale pair, kde první hodnota je enum (Direction, Area). A Direction je taky pair [DirectionId, Index], kde DirectionId je Topology dependent enum, např. (EW, NS) nebo (N, E, S, W) nebo v trojúhelníku, pyramidě a hexa (EW, NWSE, NESW), příp. (NS, NWSE, NESW). Neboli jsem právě zavedl RegionId jako 5. simple Value, takto triple [Direction, East, 1] jako první řada nebo [Area, 1, 1], kde první jednička je typicky zbytečná, protože nevím o úloze, která by využila víc než jeden druh Arey, a druhá jednička je Index, která označuje, o kterou instanci Arey jde analgicky indexu řádku v [Direction, East, 1]. Čili tenhle triple je ve skutečnosti pair<pair<enum, enum>, Index> a nejde o nový 5. typ simple Value.
Všechny simple Values lze reprezentovat jako int, jejich význam je záležitost interpretace. 

Pracuju tedy s tim, ze zakladnich typu je 6: int, set, sequence, map, tuple, variant.

Libovolná Value by měla být popsatelná jako strom zcela analogicky tomu, jak popisuju Gridy. Ano, tahle predstava je dobra: Value je strom, kde uzly tvori And a Or. Jejich konstituenty musi byt pojemnovane, jeden konstituent muze mit defaultni jmeno Value.
Je tedy treba Value<Id = "Value", Type, DefaultInput = None>
Tyto trojice lze mit preddefinovane komplet jako trojice, this is ono!

###Zamýšlený postup prací:
!!!Board je mnohem lepsi slovo nez Grid.
1) Sepsat pro každou MS2018 úlohu její normalizovaný Grid.
2) Normalizované Gridy rozkompilovat, přičemž použít jen zcela základní dělení tříd do namespaců (např. Value a Topologie zvlášť) a třídy nechat s prázdnou implementací.
3) Udělat analýzu vzniklých tříd Values, Topologies apod., porovnat ji s očekáváním, finalizovat třídy jako kanonické pro tuto verzi Logickera, zakreslit do uml.
4) Finalizovat teorii dataPresenterů, sepsat seznam convenience values, zakreslit do uml.
5) Sepsat testy pro jednotlivé dataPresentery, udělat jejich hopefully kompletní implementace.
6) Sepsat pro každou MS2018 úlohu, kde to jde, input pro assignment a solution.
7) Plnit inputama normalizované Gridy a provést na nich sanity check.
8) Sepsat pro každou MS2018 úlohu její normalizované Constraints.
9) Normalizované Constraints rozkompilovat, přičemž použít jen zcela základní dělení tříd do namespaců a třídy nechat s prázdnou implementací.
10) Udělat analýzu vzniklých Transformací a porovnat ji s očekáváním, finalizovat třídy jako kanonické pro tuto verzi Logickera, zakreslit do uml.
11) Finalizovat teorii Transformací, sepsat seznam convenience Transformací, zakreslit do uml.
12) Sepsat testy pro jednotlivé Transformace, udělat jejich hopefully kompletní implementace.
13) Pro každou úlohu MS2018 provést validity check. Když se to povede, mám Logickera.

###Dlouhodobější cíle
Kromě Logickera, který umožňuje úlohy popsat, načítat do nich data a dělat základní checky (sanity, validity), chci ještě další funkcionalitu, která bude obsahem jiných, nad Logickerem postavených projektů:
1) BenoBrok, knihovna na vytváření Solverů z Logickerových popisů.
2) GUI, které za pomoci datových struktur Logickera umožňuje úlohy zobrazit na displeji počítače a klikáním/klávesami je "řešit", tj. měnit obsah Gridu/Gridů. Lze si představit i užší propojení mezi GUI a Logickerem/BenoBrokem, které by zvýšilo uživatelský zážitek pomocí zpětné vazby nebo hintů.
3) Formátovací tentononc, umožňující sestavu úloh/řešení úloh zobrazit jako HTML pro konverzi do pdf, případně rovnou jako pdf. Je možné, že formátování se částečně překrývá s funkcionalitou v GUI.

//mno jak na ty smery, damn
//topologie by asi mela mit jeden nebo nekolik iteratoru,
//  ktere se dereferencuji na region, tj. na mnozinu policek,
//  doplnenou o informaci o regionu, tj. smeru a indexu v danem 
//  smeru
//topologie by taky mela mit metodu, kterou si lze rict
//  o konkretni region
//taky by topologie mela nejak umet to, ze kolem dokola
//  jsou taky policka; chci rict, u hexa muze nastat situace,
//  kdy se dvema ruznymi smery sousedi stejne policko vne
//  obrazce; toto je volake cudne; nevidim ted, jak na to,
//  kor kdyz v tomto pripade (Haman/2022/2kolo_11uloha) 
//  nektera policka kolem obrazce pouzita nejsou

