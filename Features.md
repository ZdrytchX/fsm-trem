# Client #

---


### Client log ###

Author: Slacker

Description: logs chat and other information to log files stored in <Tremulous home>/base/logs/

&lt;Date&gt;

.log

cl\_logs options:
```
1: logs will have prefix of 3 stars
2: logs will show game time
3: logs will show 24 hour system time
4: logs will show game and 24 hour system time
```

### VOIP Gainall ###

Author: Slacker

Description: default gain for all clients.

### AutoNameLog ###

Author: Rezyn

Description: Automatically namelogs people on connect.

### MP3 OGG support ###

Author: Thilo Schulz

Description: lets Tremulous load mp3's (for maps this is not a player)

### Calc ###

Author: Google

Description: do simple calculations

### LastVote ###

Author: Google

Description: displays last vote made

### Mapinfo ###

Author: Google

Description: displays map name

### P\_Statistics ###

Author: Google

Description: Various player statistics in a read-only cvar for binds.

```
p_hp
p_team
p_class
p_credits
p_score
p_killed
```

### VOIP Client Name and Number ###

Author: Google

Description: shows the name and number of who is talking on voip. cvar to turn this featuree on/off is cl\_voipShowSender.

### Bloom ###

Author: Harekiet

Description: This allows you to enable/disable a **bloom** effect with the in tremulous, cvar: r\_bloom, to view all the cvars, type r\_bloom in the console and press TAB.

### Cel-Shading ###

Author: Jordi Prats Catala and Guillermo Miranda Alamo

Description: This adds two cvars, r\_celoutline and r\_celshadalgo, these allow you to enable/disable the Cel-Shading effect in Tremulous

r\_celshadalgo options:
```
snn = Symmetric Nearest Neighbour

1: kuwahara
2: blur & kuwahara
3: kuwahara & blur
4: blur & kuwahara  & blur
5: snn
6: blur & snn
7: snn & blur
8: blur & snn & blur
```

### Messagemode arguments ###

Author: Benmachine

Description: Allows you to pre-set text in messagemodes, ex: /bind x messagemode FSM, will display FSM in the Say menu

### Console color controls ###

Author: Mercury

Description: This will allow you to control the color, and transparency of the console, along with the ability to control the color, transparency, and height of the bar below the console, cvar: scr\_conColor**and scr\_conBar**, to view all the cvars type /scr\_con and press TAB.

### Sort by ping works ###

Author: Amanieu

Description: Now you can view servers by ping, which didn't work in the old clients.

### Messagemode 5 ###

Author: Critux

Description: This you can bind to a key with "/bind key messagemode5", any text entered and sent will be sent to admins.

### Black to gray in console ###

Author: Benmachine

Description: This will allow you to now see black text in the console.

### Less spam in console ###

Author: Amanieu

Description: Now you don't get a buttload of text when you change maps in the console.

### Warntime ###

Author: Rezyn

Description: Displays the time, timelimit, and sudden death in the chat.

### If, math, and cvar parser ###

Author: Amanieu

Description: Allowing the usage of if, math, and cvar parsing with binds vstrs.

# Server #

---

### Backwards compatibility for cURL ###

Author: Mercury

Description: This just adds two cvars back to the server, which enables old style client cURL downloads again.