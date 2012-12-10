# Verschiedene Ideen über die KI Logik

## Steuerung des Bots

### Bewegungs KI (veraltet, wird nicht implementiert)
Wird nicht implementiert, da man keinen Vorteil hat. Am längsten Überlebt man, wenn es möglichst viele Felder gibt, die überflutet werden können. Das erreicht man indem man von anfang an versucht immer die maximal mögliche Anzahl an Feldern trockenzulegen.
* Bewege Bot zu gut bewerteten Feldern
* Bewege Bot möglichst schnell, aber nicht auf überfluteten Feldern stehen bleiben

### Trockenlegungs KI
* versuche die maximale Anzahl an Feldern pro Runde trockenzulegen
* beende deinen Zug nie auf einem überflutetem Feld
* gehe nie auf ein untergegangenes Feld


## Bewertungsmodelle

### Orts Bewertungs (wird nicht gebraucht)
* große Landflächen positiv, da man schnell ausweichen kann, bei Überflutung
	* Jedes Feld hat einen positiven Effekt auf die Umgebung
	* Überflutete Felder, negativste Bewertung
* Abstrafung für Entfernung, da reisen gefährlich ist
	* nimmt mit der Zeit zu, da reisen immer gefährlicher wird, da mehr Felder überflutet werden

### Trockenlegungs Bewertung (wird nicht wirklich gebraucht, logik implementiert ins trockenlegen)
* nur auf SEHR KURZE DISTANZ
* einzelne Felder oder Flächen mit sicherem Rand
* Versuch Inselfläche möglichst effizient zu erweitern (z.B. Inseln verbinden)
