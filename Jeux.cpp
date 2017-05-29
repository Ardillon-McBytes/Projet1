/* En-tête du programme */
///==================== */
/* Programme:		tutoGitsSFML.cpp
// Auteur:			Jean-Alain Sainton & Olivier Lemay Dostie
// Date création:	16/04/2017
// Description:		Programme des essais SFML et de connection Git pour le projet final en C++
// .				Espace de développement pour l'application.*/

/* Directives au pré-processeur */
///============================ */
#include <saisieSecurisee.h>	//Pour la fonction ouvrirFichier
#include <iomanip>				
#include <locale>				
#include <string>				
#include <vector>				
#include <math.h>				
#include <cstdlib>				
using namespace std;
#include <SFML/Graphics.hpp>	
#include <SFML/Audio.hpp>		
using namespace sf;
#include<client.h>
#include <windows.h>


/* Prototypes des fonctions */

const int NBRNIVEAU = 5;
const int NBRPOUVOIR = 10;

struct joueur
{
	string nomJoueur,
		mdpJoueur;

	int argent = 0,
		score[NBRNIVEAU][2],        // Numero niveau | Score attein
		pouvoir[NBRPOUVOIR][2],		//Numero pouvoir | acheter(1) ou non (2)
		niveauDebloquer = 0;
};

struct boutonClick
{
	int posXRect = 350,
		posYRect = 50,
		hauteur = 50,
		largeur = 300,
		posXTexte = 375,
		posYTexte = 75;
	RectangleShape rectangle;
	Texture fondImage;
	Text text;
	Font font;
};

void menuLogIn();
string saisieTexte(RenderWindow & window, RectangleShape rectangle, Text &text, Font &font);
string saisieTexteCacher(RenderWindow & window, RectangleShape rectangle, Text &text, Font &font);
void main() {

	int choixMenu = 0,
		choixNiveau = 0,
		mouvement = 0, // (1=haut, 2=bas, 3=gauche 4=droite)
		action = 0, // ()
		typeMonstre = 0,
		niveauChoisie = 0;


	menuLogIn();
	//conectionWinsock(argc, argv);
}

void menuLogIn()
{
	int argc = 0;
	char *argv[15];
	RenderWindow window;
	joueur joueur;
	Font fontTitre;
	if (!fontTitre.loadFromFile("hemi_head_bd_it.ttf"));		//Si la police n'est pas trouvable, une erreur est afficher dans la console

	/*Font font;
	if (!font.loadFromFile("styles/font_arial.ttf"));*/


	Music music;
	Music music2;
	Music music3;

	Texture texture;

	if (!texture.loadFromFile("background.png"));		//Si la texture n'est pas trouvable, une erreur est afficher dans la console
	Texture textureBtnIntro;
	if (!textureBtnIntro.loadFromFile("telechargement.jpg"));
	window.create(VideoMode::getDesktopMode(), "Log In");
	const int HAUTEURWINDOW = window.getSize().y;
	const int LARGEURWINDOW = window.getSize().x;

	Sprite background(texture);

	Text infoUtilisateur[2];
	const int NBRTEXT = 2;
	const int NBRBOUTON = 4;
	boutonClick bouton[NBRBOUTON];
	while (window.isOpen())
	{
		window.draw(background);
		for (size_t i = 0; i < NBRBOUTON; i++)
		{
			bouton[i].rectangle.setFillColor(Color::White);
			bouton[i].rectangle.setOutlineThickness(5);  //défini la grosseur de la bordure
			bouton[i].rectangle.setOutlineColor(Color::Red); //défini la couleur de la bordure
			bouton[i].text.setCharacterSize(30);
			bouton[i].text.setStyle(Text::Bold);
			bouton[i].text.setColor(Color::Green);
			bouton[i].fondImage.setSmooth(true);
			bouton[i].text.setFont(fontTitre);
			bouton[i].rectangle.setSize(Vector2f(350, 150));
			bouton[i].rectangle.setTexture(&textureBtnIntro);
		}

		bouton[0].rectangle.setPosition((LARGEURWINDOW / 2) - (bouton[0].rectangle.getSize().x / 2), HAUTEURWINDOW / 3 - (bouton[0].rectangle.getSize().y / 2));
		bouton[1].rectangle.setPosition((LARGEURWINDOW / 2) - (bouton[1].rectangle.getSize().x / 2), HAUTEURWINDOW / 3 - (bouton[1].rectangle.getSize().y / 2) + (bouton[0].rectangle.getSize().y * 2));

		bouton[2].rectangle.setPosition((LARGEURWINDOW / 4) , HAUTEURWINDOW - (HAUTEURWINDOW / 4) );
		bouton[3].rectangle.setPosition((LARGEURWINDOW / 1.75)  , HAUTEURWINDOW - (HAUTEURWINDOW / 4));

		int btnNomX = bouton[0].rectangle.getPosition().x - ((bouton[0].rectangle.getSize().x));
		int btnNomy = bouton[0].rectangle.getPosition().y + (bouton[0].rectangle.getSize().y / 2.5);
		int btnMdpX = bouton[1].rectangle.getPosition().x - ((bouton[1].rectangle.getSize().x));
		int btnMdpy = bouton[1].rectangle.getPosition().y + (bouton[1].rectangle.getSize().y / 2.5);

		int btnConectX = bouton[2].rectangle.getPosition().x + ((bouton[2].rectangle.getSize().x /3));
		int btnConectY = bouton[2].rectangle.getPosition().y + (bouton[2].rectangle.getSize().y / 2.5);
		int btnQuitX = bouton[3].rectangle.getPosition().x + ((bouton[3].rectangle.getSize().x/3));
		int btnQuitY = bouton[3].rectangle.getPosition().y + (bouton[3].rectangle.getSize().y / 2.5);


		bouton[0].text.setPosition(btnNomX, btnNomy);
		bouton[1].text.setPosition(btnMdpX, btnMdpy);
		bouton[2].text.setPosition(btnConectX, btnConectY);
		bouton[3].text.setPosition(btnQuitX, btnQuitY);

	
		bouton[0].text.setString("Nom du joueur" + '\0');
		bouton[1].text.setString("Mot de passe" + '\0');
		bouton[2].text.setString("Connecter" + '\0');
		bouton[3].text.setString("Quitter" + '\0');

		Event event;
		int reponse = 0;
		while (window.waitEvent(event))
		{
			window.draw(background);
			for (size_t i = 0; i < NBRBOUTON; i++)
			{
				window.draw(bouton[i].rectangle);
				window.draw(bouton[i].text);
			}

			for (size_t i = 0; i < NBRTEXT; i++)
			{
				window.draw(infoUtilisateur[i]);
			}
				
			
			window.display();
			if ((event.mouseMove.x > bouton[0].rectangle.getPosition().x && event.mouseMove.x < (bouton[0].rectangle.getPosition().x + bouton[0].rectangle.getSize().x))
				&& (event.mouseMove.y > bouton[0].rectangle.getPosition().y && event.mouseMove.y < (bouton[0].rectangle.getPosition().y + bouton[0].rectangle.getSize().y)))
			{

				bouton[0].rectangle.setOutlineColor(Color::Blue);
			

			}
			else
			{
				bouton[0].rectangle.setOutlineColor(Color::Red);
				
			}
			if ((event.mouseMove.x > bouton[1].rectangle.getPosition().x && event.mouseMove.x < (bouton[1].rectangle.getPosition().x + bouton[1].rectangle.getSize().x))
				&& (event.mouseMove.y > bouton[1].rectangle.getPosition().y && event.mouseMove.y < (bouton[1].rectangle.getPosition().y + bouton[1].rectangle.getSize().y)))
			{

				bouton[1].rectangle.setOutlineColor(Color::Blue);


			}
			else
			{
				bouton[1].rectangle.setOutlineColor(Color::Red);

			}
			switch (event.type)
			{
			case Event::Closed:
				exit(0);
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
				{// S l'utilisateur appuis que la touche echap, ferme le menu d'option et retourne au menu ou au jeu
					window.setVisible(true);
					exit(0);
				}

			case Event::MouseButtonPressed:
				Mouse::getPosition(window);
				if ((event.mouseButton.x > bouton[0].rectangle.getPosition().x && event.mouseButton.x < (bouton[0].rectangle.getPosition().x + bouton[0].rectangle.getSize().x))
					&& (event.mouseButton.y > bouton[0].rectangle.getPosition().y && event.mouseButton.y < (bouton[0].rectangle.getPosition().y + bouton[0].rectangle.getSize().y)))
				{
					bouton[0].rectangle.setFillColor(Color::Magenta);
					infoUtilisateur[0].setColor(Color::White);
					window.draw(infoUtilisateur[0]);
					window.draw(bouton[0].rectangle);
					window.display();
					infoUtilisateur[0].setString(saisieTexte(window, bouton[0].rectangle, infoUtilisateur[0], fontTitre));
					bouton[0].rectangle.setFillColor(Color::White);
					infoUtilisateur[0].setColor(Color::Black);

				}
				
				else if ((event.mouseButton.x > bouton[1].rectangle.getPosition().x && event.mouseButton.x < (bouton[1].rectangle.getPosition().x + bouton[1].rectangle.getSize().x))
					&& (event.mouseButton.y > bouton[1].rectangle.getPosition().y && event.mouseButton.y < (bouton[1].rectangle.getPosition().y + bouton[1].rectangle.getSize().y)))
				{
					bouton[1].rectangle.setFillColor(Color::Magenta);
					infoUtilisateur[1].setColor(Color::White);
					window.draw(infoUtilisateur[1]);
					window.draw(bouton[1].rectangle);
					window.display();
					infoUtilisateur[1].setString(saisieTexteCacher(window, bouton[1].rectangle, infoUtilisateur[1], fontTitre));
					bouton[1].rectangle.setFillColor(Color::White);
					infoUtilisateur[1].setColor(Color::Black);

				}
				else if ((event.mouseButton.x > bouton[2].rectangle.getPosition().x && event.mouseButton.x < (bouton[2].rectangle.getPosition().x + bouton[2].rectangle.getSize().x))
					&& (event.mouseButton.y > bouton[2].rectangle.getPosition().y && event.mouseButton.y < (bouton[2].rectangle.getPosition().y + bouton[2].rectangle.getSize().y)))
				{

					bouton[2].rectangle.setFillColor(Color::Magenta);
					return;
				}
				else 	if ((event.mouseButton.x > bouton[3].rectangle.getPosition().x && event.mouseButton.x < (bouton[3].rectangle.getPosition().x + bouton[3].rectangle.getSize().x))
					&& (event.mouseButton.y > bouton[3].rectangle.getPosition().y && event.mouseButton.y < (bouton[3].rectangle.getPosition().y + bouton[3].rectangle.getSize().y)))
				{
					bouton[3].rectangle.setFillColor(Color::Magenta);
				
				}

			}
		}
	}
}
	



	string saisieTexte(RenderWindow & window, RectangleShape rectangle, Text &text, Font &font)
	{
		Event event;
		string s = text.getString();
		
		text.setPosition(rectangle.getPosition().x + 15, rectangle.getPosition().y + (rectangle.getSize().y / 2.5));		// position du texte
		text.setFont(font);
		while (window.waitEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				exit(0);
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
				{// S l'utilisateur appuis que la touche echap, ferme le menu d'option et retourne au menu ou au jeu
					window.setVisible(true);
					exit(0);
				}
			case Event::MouseButtonPressed:
				Mouse::getPosition(window);

				
				do
				{
					while (window.waitEvent(event)) {
						

						if (event.type == Event::Closed)
							window.close();

						if (event.type == Event::TextEntered) {
							if (event.key.code == Keyboard::Escape)
								window.close();
							if (event.key.code == 8 && s.size() != 0)		//touche backspace
							{
								s.pop_back();  //Enleve le dernier char dans la string
							}
							else if (event.key.code == 13) //touche enter
							{
								if (s.size() != 0)
								{
									text.setString (s);
									return s;
								}
							}
							else if (
								((event.key.code >= 97 && event.key.code <= 122)
									|| event.key.code == 32 || (event.key.code == Keyboard::RShift || event.key.code == Keyboard::LShift)
									|| (event.key.code >= 48 && event.key.code <= 57))
								&& (s.size() <= 10))	// caractere ASCII (A - Z, 0 - 9 )
							{
								s.push_back((char)event.text.unicode); // ajoute un char a la string
							}



							window.draw(rectangle);	//Affiche un rectangle vide

							text.setString(s); 	// choix de la chaîne de caractères à afficher
							

							window.draw(text);

							window.display();
						}
					}
				} while (true);

			}
		}

	}

	string saisieTexteCacher(RenderWindow & window, RectangleShape rectangle, Text &text, Font &font)
	{
		Event event;
		string s = text.getString();
		string mdpCacher;
		text.setPosition(rectangle.getPosition().x + 15, rectangle.getPosition().y + (rectangle.getSize().y / 2.5));		// position du texte
		text.setFont(font);
		while (window.waitEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				exit(0);
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
				{// S l'utilisateur appuis que la touche echap, ferme le menu d'option et retourne au menu ou au jeu
					window.setVisible(true);
					exit(0);
				}
			case Event::MouseButtonPressed:
				Mouse::getPosition(window);


				do
				{
					while (window.pollEvent(event)) {


						if (event.type == Event::Closed)
							window.close();

						if (event.type == Event::TextEntered) {
							if (event.key.code == Keyboard::Escape)
								window.close();
							if (event.key.code == 8 && s.size() != 0)		//touche backspace
							{
								s.pop_back();  //Enleve le dernier char dans la string
								mdpCacher.pop_back();
							}
							else if (event.key.code == 13) //touche enter
							{
								if (s.size() != 0)
								{
									text.setString(s);
									return mdpCacher;
								}
							}
							else if (
								((event.key.code >= 97 && event.key.code <= 122)
									|| event.key.code == 32 || (event.key.code == Keyboard::RShift || event.key.code == Keyboard::LShift)
									|| (event.key.code >= 48 && event.key.code <= 57))
								&& (s.size() <= 10))	// caractere ASCII (A - Z, 0 - 9 )
							{
								s.push_back((char)event.text.unicode); // ajoute un char a la string
								mdpCacher += '*';
							}



							window.draw(rectangle);	//Affiche un rectangle vide

							text.setString(mdpCacher); 	// choix de la chaîne de caractères à afficher


							window.draw(text);

							window.display();
						}
					}
				} while (true);

			}
		}

	}