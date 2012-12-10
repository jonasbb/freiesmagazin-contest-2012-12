# Verschiedene Ideen über die KI Logik

## Steuerung des Bots

### Bewegungs KI
* Bewege Bot zu gut bewerteten Feldern
* Bewege Bot möglichst schnell, aber nicht auf überfluteten Feldern stehen bleiben

### Trockenlegungs KI
* Einmal an einem guten Platz, versuche neue Felder trockenzulegen
* lege einzelne Felder sehr schnell trocken
* oder größere Flächen, solange man einen sicheren Rand hat


## Bewertungsmodelle

### Orts Bewertungs
* große Landflächen positiv, da man schnell ausweichen kann, bei Überflutung
	* Jedes Feld hat einen positiven Effekt auf die Umgebung
	* Überflutete Felder, negativste Bewertung
* Abstrafung für Entfernung, da reisen gefährlich ist
	* nimmt mit der Zeit zu, da reisen immer gefährlicher wird, da mehr Felder überflutet werden

### Trockenlegungs Bewertung
* nur auf SEHR KURZE DISTANZ
* einzelne Felder oder Flächen mit sicherem Rand
* Versuch Inselfläche möglichst effizient zu erweitern (z.B. Inseln verbinden)
