# WarGame_C
C project - War Game

### About Project:
 It's first semester C project. Or more precize my attempt to this project. Coding in C is like "building house with one hand". At least it how I feel. Maybe with more C knowlge it will be better.. We will see next semester.<br>
 **Examples** folder contains code snipets not related to the project.<br>
 **old** folder contains old code wich was once part of project. I keep it just for historical purposes.<br>
 **src** folder is were project lives.

 #### Some rules(more in pdf file):
- How	the	program	should	operate:

    - Every	time	a	new	game	is	created	the	program	should	ask	how	many players	are	playing	and	the	player’s	cards	should	then be	randomly	generated.
    - If	a	saved	game	is	loaded,	then	the	program	should	display	the	current	status	of	the	game.
    - Once	the	game	is	loaded	the	users	should	be	presented	with	a	number	of	options:
    - Complete	the	next	round
    - Save	the	game
    - Output	the	games	status
    - Exit	the	game	without	saving:
        - Selecting	this	option	exits	the	game	but	you	are	then	given	the	following	options:
            - Open	a	new	game
            - Open	a	previously	save	game
            - Exit	the	application
- Special	Rules	&	Notes:
    - Each	player	gets	13	cards	-	**one	of	each**	"suit"
    - Player	can	see	that	cards	in	their	hand	but	cannot	see	their	opponent’s	cards.
    - No dublicates can win.
    - Roll over Points if no winner.
> ALL	TIE	RULE:		If	all	cards	tie	another	(example	of	5	players:		_A,8,8,A,8_)	-	then	those	points	are	rolled	over	to	the	next	round	-	making	the	next	round	a	VERY	important	round.		If	a	tie	like	this	happens	on	the	last	round,	then	those	points	are	just	"lost	on	the	battlefield"

### Steps I planing to do:
- **Players:**
 - Use `struct` to create player.
 - Store all players in array.
- **Cards:**
    - Use `struct` to create card.
    - Store all players cards in 2D array `cardArry[player][card]`
    - Deal random cards to each player. Make sure player has at least one of each suit.
    - Store "cards on the table" in separete array. In array index of card will mach index of player in players list array.
- **Game logic:**
    - Wins the highest value card.
    - No dublicate card can win. Winns only  _**unique**_ card.
    - If no winner at the current round points roll over to next round.
- **Save/Load game:**
    - At games loading time check if here is any previously saved games. If yes, ask would user like to load the game.
    - Auto save game on each round to special file(extra).
    - On exist ask use if he wants to save game progress.
        - if yes, user shold enter name of save and game progres should be saved to this save.
        - if no, exit game.
