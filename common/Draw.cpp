#include "Game.h"

void Game::Draw() {

	if (gamestart) {
        // draw background
		if (change_bg||globe_style_mode!=gamestart_style) {
			gamestart_style = globe_style_mode;
			if (globe_style_mode==1){
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_dark.png", 0, 0, 1, 1);
				// for normal button
				Load_Image(gamestart_go.texture_normal, gamestart_go.sprite_normal, "image/back_stable/start-surface/start-light-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_normal, gamestart_info.sprite_normal, "image/back_stable/start-surface/start-light-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_normal, gamestart_quit.sprite_normal, "image/back_stable/start-surface/start-light-button-quit.png", 0, 0, 1, 1);
				// for high light button
				Load_Image(gamestart_go.texture_hover, gamestart_go.sprite_hover, "image/back_stable/start-surface/start-dark-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_hover, gamestart_info.sprite_hover, "image/back_stable/start-surface/start-dark-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_hover, gamestart_quit.sprite_hover, "image/back_stable/start-surface/start-dark-button-quit.png", 0, 0, 1, 1);
			}
			else if (globe_style_mode == 0) {
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_light.png", 0, 0, 1, 1);
				// for normal button
				Load_Image(gamestart_go.texture_normal, gamestart_go.sprite_normal, "image/back_stable/start-surface/start-dark-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_normal, gamestart_info.sprite_normal, "image/back_stable/start-surface/start-dark-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_normal, gamestart_quit.sprite_normal, "image/back_stable/start-surface/start-dark-button-quit.png", 0, 0, 1, 1);
				// for high light button
				Load_Image(gamestart_go.texture_hover, gamestart_go.sprite_hover, "image/back_stable/start-surface/start-light-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_hover, gamestart_info.sprite_hover, "image/back_stable/start-surface/start-light-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_hover, gamestart_quit.sprite_hover, "image/back_stable/start-surface/start-light-button-quit.png", 0, 0, 1, 1);
			}
			change_bg = false;
		}

		sprite_gamestart_bg.setPosition(0, 0);
		window.draw(sprite_gamestart_bg);
		if (button_animate_count < 81) {
			window.setFramerateLimit(200);
			if(gamestart_go.is_hover)	gamestart_go.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
			if (gamestart_info.is_hover)gamestart_info.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
			if (gamestart_quit.is_hover)gamestart_quit.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
			button_animate_count++;
			if (button_animate_count == 81)
				window.setFramerateLimit(300);
		}
		/// for start go button
		gamestart_go.sprite_normal.setPosition(570, 50);
		window.draw(gamestart_go.sprite_normal);
		if (gamestart_go.is_hover) {
			gamestart_go.sprite_hover.setPosition(570, 50);
			window.draw(gamestart_go.sprite_hover);
		}
		else if (gamestart_go.is_down) {
			gamestart_go.sprite_down.setPosition(570, 50);
			window.draw(gamestart_go.sprite_down);
		}
		/// for start info button
		gamestart_info.sprite_normal.setPosition(470, 90);
		window.draw(gamestart_info.sprite_normal);
		if (gamestart_info.is_hover) {
			gamestart_info.sprite_hover.setPosition(470, 90);
			window.draw(gamestart_info.sprite_hover);
		}
		else if (gamestart_info.is_down) {
			gamestart_info.sprite_down.setPosition(470, 90);
			window.draw(gamestart_info.sprite_down);
		}
		/// for start quit button
		gamestart_quit.sprite_normal.setPosition(370, 130);
		window.draw(gamestart_quit.sprite_normal);
		if (gamestart_quit.is_hover) {
			gamestart_quit.sprite_hover.setPosition(370, 130);
			window.draw(gamestart_quit.sprite_hover);
		}
		else if (gamestart_quit.is_down) {
			gamestart_quit.sprite_down.setPosition(370, 130);
			window.draw(gamestart_quit.sprite_down);
		}
	}

	if (net_chosen) {
		// draw background
		if (change_bg || globe_style_mode != gamechoose_style) {
			gamechoose_style = globe_style_mode;
			if (globe_style_mode == 1) {
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_dark.png", 0, 0, 1, 1);
				// for container
				Load_Image(texture_netchoose_contain, sprite_netchoose_contain, "image/back_stable/chosen-surface/chosen-net-word-dark.png", 0, 0, 1, 1);
				// for chosen button
				Load_Image(button_gamechoose.texture_hover, button_gamechoose.sprite_hover, "image/back_stable/chosen-surface/chosen-button-dark.png", 0, 0, 1, 1);
			}
			else if (globe_style_mode == 0) {
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_light.png", 0, 0, 1, 1);
				// for container
				Load_Image(texture_netchoose_contain, sprite_netchoose_contain, "image/back_stable/chosen-surface/chosen-net-word-light.png", 0, 0, 1, 1);
				// for chosen button
				Load_Image(button_gamechoose.texture_hover, button_gamechoose.sprite_hover, "image/back_stable/chosen-surface/chosen-button-light.png", 0, 0, 1, 1);
			}
			change_bg = false;
		}

		sprite_gamestart_bg.setPosition(0, 0);
		window.draw(sprite_gamestart_bg);

		sprite_netchoose_contain.setPosition(315, 75);
		window.draw(sprite_netchoose_contain);

		/// for chosen button  (hover)
		if (button_gamechoose.is_hover) {
			window.draw(button_gamechoose.sprite_hover);
		}

		// the mask
		if (globe_style_mode == 0) {
			RectangleShape rect(Vector2f(140, 200)); // draw rectangle
			rect.setFillColor(Color(255, 255, 255, 255));
			rect.setPosition(880, 580);
			window.draw(rect);
		}
		else if (globe_style_mode == 1) {
			RectangleShape rect(Vector2f(140, 200)); // draw rectangle
			rect.setFillColor(Color(0, 0, 0, 255));
			rect.setPosition(880, 580);
			window.draw(rect);
		}

		/// for draw return button
		if (return_button.is_normal) {
			return_button.sprite_normal.setPosition(900, 650);
			window.draw(return_button.sprite_normal);
		}
		else if (return_button.is_hover) {
			return_button.sprite_hover.setPosition(880, 630);
			window.draw(return_button.sprite_hover);
		}
		else if (return_button.is_down) {
			return_button.sprite_down.setPosition(900, 650);
			window.draw(return_button.sprite_down);
		}
	}

	if (gamechoose) {
		// draw background
		if (change_bg || globe_style_mode != gamechoose_style) {
			gamechoose_style = globe_style_mode;
			if (globe_style_mode == 1) {
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_dark.png", 0, 0, 1, 1);
				// for container
				Load_Image(texture_gamechoose_contain, sprite_gamechoose_contain, "image/back_stable/chosen-surface/chosen-word-dark.png", 0, 0, 1, 1);
				// for chosen button
				Load_Image(button_gamechoose.texture_hover, button_gamechoose.sprite_hover, "image/back_stable/chosen-surface/chosen-button-dark.png", 0, 0, 1, 1);
			}
			else if (globe_style_mode == 0) {
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_light.png", 0, 0, 1, 1);
				// for container
				Load_Image(texture_gamechoose_contain, sprite_gamechoose_contain, "image/back_stable/chosen-surface/chosen-word-light.png", 0, 0, 1, 1);
				// for chosen button
				Load_Image(button_gamechoose.texture_hover, button_gamechoose.sprite_hover, "image/back_stable/chosen-surface/chosen-button-light.png", 0, 0, 1, 1);
			}
			change_bg = false;
		}

		sprite_gamestart_bg.setPosition(0, 0);
		window.draw(sprite_gamestart_bg);

		sprite_gamechoose_contain.setPosition(315, 75);
		window.draw(sprite_gamechoose_contain);
	
		/// for chosen button  (hover)
		if (button_gamechoose.is_hover) {
			
			window.draw(button_gamechoose.sprite_hover);
		}

		// the mask
		if (globe_style_mode == 0) {
			RectangleShape rect(Vector2f(140, 200)); // draw rectangle
			rect.setFillColor(Color(255, 255, 255,255));
			rect.setPosition(880, 580);
			window.draw(rect);
		}
		else if (globe_style_mode == 1) {
			RectangleShape rect(Vector2f(140, 200)); // draw rectangle
			rect.setFillColor(Color(0, 0,0, 255));
			rect.setPosition(880, 580);
			window.draw(rect);
		}

		/// for draw return button
		if (return_button.is_normal) {
			return_button.sprite_normal.setPosition(900, 650);
			window.draw(return_button.sprite_normal);
		}
		else if (return_button.is_hover) {
			return_button.sprite_hover.setPosition(880, 630);
			window.draw(return_button.sprite_hover);
		}
		else if (return_button.is_down) {
			return_button.sprite_down.setPosition(900, 650);
			window.draw(return_button.sprite_down);
		}
	}

	if (gameinfo) {
		// draw stable background
		if (change_bg||globe_style_mode!=gameinfo_style) {
			gameinfo_style = globe_style_mode;
			if (globe_style_mode == 0) {
				// for background
				Load_Image(texture_gameinfo_bg, sprite_gameinfo_bg, "image/back_stable/info-surface/bg-light.png", 0, 0, 1, 1);
				// normal 
				Load_Image(gameinfo_thanks.texture_normal, gameinfo_thanks.sprite_normal, "image/back_stable/info-surface/thanksinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_gameinfo.texture_normal, gameinfo_gameinfo.sprite_normal, "image/back_stable/info-surface/gameinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_phaseinfo.texture_normal, gameinfo_phaseinfo.sprite_normal, "image/back_stable/info-surface/phaseinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_cardinfo.texture_normal, gameinfo_cardinfo.sprite_normal, "image/back_stable/info-surface/cardinfo-button-light.png", 0, 0, 1, 1);
				// high light 
				Load_Image(gameinfo_thanks.texture_hover, gameinfo_thanks.sprite_hover, "image/back_stable/info-surface/thanksinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_gameinfo.texture_hover, gameinfo_gameinfo.sprite_hover, "image/back_stable/info-surface/gameinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_phaseinfo.texture_hover, gameinfo_phaseinfo.sprite_hover, "image/back_stable/info-surface/phaseinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_cardinfo.texture_hover, gameinfo_cardinfo.sprite_hover, "image/back_stable/info-surface/cardinfo-button-dark.png", 0, 0, 1, 1);
				// down
				Load_Image(gameinfo_thanks.texture_down, gameinfo_thanks.sprite_down, "image/back_stable/info-surface/thanksinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_gameinfo.texture_down, gameinfo_gameinfo.sprite_down, "image/back_stable/info-surface/gameinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_phaseinfo.texture_down, gameinfo_phaseinfo.sprite_down, "image/back_stable/info-surface/phaseinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_cardinfo.texture_down, gameinfo_cardinfo.sprite_down, "image/back_stable/info-surface/cardinfo-button-dark.png", 0, 0, 1, 1);
				// for word style
				Load_Image(texture_gameinfo_thanks, sprite_gameinfo_thanks, "image/back_stable/info-surface/thanks-light.png", 0, 0, 1, 1);
				Load_Image(texture_gameinfo_gameinfo, sprite_gameinfo_gameinfo, "image/back_stable/info-surface/gameinfo-light.png", 0, 0, 1, 1);
				Load_Image(texture_gameinfo_phaseinfo, sprite_gameinfo_phaseinfo, "image/back_stable/info-surface/phaseinfo-light.png", 0, 0, 1, 1);
				Load_Image(texture_gameinfo_cardinfo, sprite_gameinfo_cardinfo, "image/back_stable/info-surface/cardinfo-light.png", 0, 0, 1, 1);

			}
			else if (globe_style_mode == 1) {
				// for background
				Load_Image(texture_gameinfo_bg, sprite_gameinfo_bg, "image/back_stable/info-surface/bg-dark.png", 0, 0, 1, 1);
				// normal 
				Load_Image(gameinfo_thanks.texture_normal, gameinfo_thanks.sprite_normal, "image/back_stable/info-surface/thanksinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_gameinfo.texture_normal, gameinfo_gameinfo.sprite_normal, "image/back_stable/info-surface/gameinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_phaseinfo.texture_normal, gameinfo_phaseinfo.sprite_normal, "image/back_stable/info-surface/phaseinfo-button-dark.png", 0, 0, 1, 1);
				Load_Image(gameinfo_cardinfo.texture_normal, gameinfo_cardinfo.sprite_normal, "image/back_stable/info-surface/cardinfo-button-dark.png", 0, 0, 1, 1);
				// high dark 
				Load_Image(gameinfo_thanks.texture_hover, gameinfo_thanks.sprite_hover, "image/back_stable/info-surface/thanksinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_gameinfo.texture_hover, gameinfo_gameinfo.sprite_hover, "image/back_stable/info-surface/gameinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_phaseinfo.texture_hover, gameinfo_phaseinfo.sprite_hover, "image/back_stable/info-surface/phaseinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_cardinfo.texture_hover, gameinfo_cardinfo.sprite_hover, "image/back_stable/info-surface/cardinfo-button-light.png", 0, 0, 1, 1);
				// down
				Load_Image(gameinfo_thanks.texture_down, gameinfo_thanks.sprite_down, "image/back_stable/info-surface/thanksinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_gameinfo.texture_down, gameinfo_gameinfo.sprite_down, "image/back_stable/info-surface/gameinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_phaseinfo.texture_down, gameinfo_phaseinfo.sprite_down, "image/back_stable/info-surface/phaseinfo-button-light.png", 0, 0, 1, 1);
				Load_Image(gameinfo_cardinfo.texture_down, gameinfo_cardinfo.sprite_down, "image/back_stable/info-surface/cardinfo-button-light.png", 0, 0, 1, 1);
				// for word style
				Load_Image(texture_gameinfo_thanks, sprite_gameinfo_thanks, "image/back_stable/info-surface/thanks-dark.png", 0, 0, 1, 1);
				Load_Image(texture_gameinfo_gameinfo, sprite_gameinfo_gameinfo, "image/back_stable/info-surface/gameinfo-dark.png", 0, 0, 1, 1);
				Load_Image(texture_gameinfo_phaseinfo, sprite_gameinfo_phaseinfo, "image/back_stable/info-surface/phaseinfo-dark.png", 0, 0, 1, 1);
				Load_Image(texture_gameinfo_cardinfo, sprite_gameinfo_cardinfo, "image/back_stable/info-surface/cardinfo-dark.png", 0, 0, 1, 1);
			}
			change_bg = false;
		}
		// draw background
		sprite_gameinfo_bg.setPosition(0, 0);
		window.draw(sprite_gameinfo_bg);
		// draw word box
		if (gameinfo_thanks.is_down) {
			sprite_gameinfo_thanks.setPosition(77, 57);
			window.draw(sprite_gameinfo_thanks);
		}
		else if (gameinfo_gameinfo.is_down) {
			sprite_gameinfo_gameinfo.setPosition(92, 56);
			window.draw(sprite_gameinfo_gameinfo);
		}
		else if (gameinfo_phaseinfo.is_down) {
			sprite_gameinfo_phaseinfo.setPosition(32, 58);
			window.draw(sprite_gameinfo_phaseinfo);
		}
		else if (gameinfo_cardinfo.is_down) {
			sprite_gameinfo_cardinfo.setPosition(33, 56);
			window.draw(sprite_gameinfo_cardinfo);
		}

		if (button_animate_count < 37) {
			window.setFramerateLimit(200);
			if (gameinfo_thanks.is_hover)	gameinfo_thanks.sprite_hover.setTextureRect(IntRect(0, 0, 86, button_animate_count * 5));
			if (gameinfo_gameinfo.is_hover)gameinfo_gameinfo.sprite_hover.setTextureRect(IntRect(0, 0, 86, button_animate_count * 5));
			if (gameinfo_phaseinfo.is_hover)gameinfo_phaseinfo.sprite_hover.setTextureRect(IntRect(0, 0, 86, button_animate_count * 5));
			if (gameinfo_cardinfo.is_hover)gameinfo_cardinfo.sprite_hover.setTextureRect(IntRect(0, 0, 86, button_animate_count * 5));
			button_animate_count++;
			if (button_animate_count == 38)
				window.setFramerateLimit(300);
		}
		/// for thanks button
		gameinfo_thanks.sprite_normal.setPosition(459, 445);
		window.draw(gameinfo_thanks.sprite_normal);
		if (gameinfo_thanks.is_hover) {
			gameinfo_thanks.sprite_hover.setPosition(459, 445);
			window.draw(gameinfo_thanks.sprite_hover);
		}
		else if (gameinfo_thanks.is_down) {
			gameinfo_thanks.sprite_down.setPosition(459, 445);
			window.draw(gameinfo_thanks.sprite_down);
		}
		/// for gameinfo button
		gameinfo_gameinfo.sprite_normal.setPosition(529, 430);
		window.draw(gameinfo_gameinfo.sprite_normal);
		if (gameinfo_gameinfo.is_hover) {
			gameinfo_gameinfo.sprite_hover.setPosition(529, 430);
			window.draw(gameinfo_gameinfo.sprite_hover);
		}
		else if (gameinfo_gameinfo.is_down) {
			gameinfo_gameinfo.sprite_down.setPosition(529, 430);
			window.draw(gameinfo_gameinfo.sprite_down);
		}
		/// for info phaseinfo button
		gameinfo_phaseinfo.sprite_normal.setPosition(603, 430);
		window.draw(gameinfo_phaseinfo.sprite_normal);
		if (gameinfo_phaseinfo.is_hover) {
			gameinfo_phaseinfo.sprite_hover.setPosition(603, 430);
			window.draw(gameinfo_phaseinfo.sprite_hover);
		}
		else if (gameinfo_phaseinfo.is_down) {
			gameinfo_phaseinfo.sprite_down.setPosition(603, 430);
			window.draw(gameinfo_phaseinfo.sprite_down);
		}
		/// for info cardinfo button
		gameinfo_cardinfo.sprite_normal.setPosition(673,430);
		window.draw(gameinfo_cardinfo.sprite_normal);
		if (gameinfo_cardinfo.is_hover) {
			gameinfo_cardinfo.sprite_hover.setPosition(673, 430);
			window.draw(gameinfo_cardinfo.sprite_hover);
		}
		else if (gameinfo_cardinfo.is_down) {
			gameinfo_cardinfo.sprite_down.setPosition(673, 430);
			window.draw(gameinfo_cardinfo.sprite_down);
		}

		/// for draw return button
		if (return_button.is_normal) {
			return_button.sprite_normal.setPosition(900, 650);
			window.draw(return_button.sprite_normal);
		}
		else if (return_button.is_hover) {
			return_button.sprite_hover.setPosition(880, 630);
			window.draw(return_button.sprite_hover);
		}
		else if (return_button.is_down) {
			return_button.sprite_down.setPosition(900, 650);
			window.draw(return_button.sprite_down);
		}
	}

	if (gamerun||gamepause||gameover) {
		// draw stable part
		Draw_Stable_Background();

		// draw text console
		if(game_model == single_player) Draw_Text_Console();

		// draw discard pile
		if (game_model == single_player) Draw_Discard_Pile();

		// draw human part
		Draw_HumanPlayer();
		Draw_Animator_Human();

		//draw machine part --stable
		for (int number = 0; number < machine_number; number++) {
			Draw_Machine(Machine[number]);
		}
		//draw machine part --animation
		for (int number = 0; number < machine_number; number++) {
			Draw_Animator_Machine(Machine[number]);
		}
		
		// draw pause button
		if (gamerun) {
			/// for draw pause button
			if (pause_button.is_normal) {
				pause_button.sprite_normal.setPosition(0, -12);
				window.draw(pause_button.sprite_normal);
			}
			else if (pause_button.is_hover) {
				pause_button.sprite_hover.setPosition(-4, -12);
				window.draw(pause_button.sprite_hover);
			}
			else if (pause_button.is_down) {
				pause_button.sprite_down.setPosition(0, -12);
				window.draw(pause_button.sprite_down);
			}
		}

		// show temp-pile card where using amazing grace
		if (exturn == human && Human.skill.amazing_grace_state) {
            // draw back-stable ground
			RectangleShape bg_rect(Vector2f((100*temp_pile.Pile_Card_Amount+20)>319? (100 * temp_pile.Pile_Card_Amount + 20):320, 180)); // draw rectangle
			bg_rect.setFillColor(Color(0, 0, 0, 100));
			bg_rect.setPosition(260, 410);
			window.draw(bg_rect);

			// draw remind note
			Font reminded_note_font;
			Text reminded_note;
			Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
			reminded_note.setCharacterSize(20);
			reminded_note.setFillColor(Color(255, 255, 255, 255));
			reminded_note.setStyle(Text::Bold);
			reminded_note.setPosition(265, 415);
			wstring reminded = L"五谷丰登--请选择一张牌收入囊中";
			reminded_note.setString(reminded);
			window.draw(reminded_note);


			Single_Card* ptr = temp_pile.Pile_Card_Total->next;
			for (int i = 0; i < temp_pile.Pile_Card_Amount; i++) {  // each card:  width 93 || height 130
				ptr->point_one.x = 270 + i * 100;
				ptr->point_one.y = 450;
				ptr->point_two.x = ptr->point_one.x + 93;
				ptr->point_two.y = ptr->point_one.y + 130;
				if (ptr->mouse_select_card) {
					ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
					window.draw(ptr->sprite_card);

					RectangleShape rect(Vector2f(93, 130)); // draw rectangle
					rect.setFillColor(Color(155, 0, 0, 100));
					rect.setPosition(ptr->point_one.x, ptr->point_one.y);
					window.draw(rect);
				}
				else {
					ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
					window.draw(ptr->sprite_card);
				}
				//window.draw(ptr->sprite_card);
				ptr = ptr->next;
			}
		}
        
	}

	if (gamepause) {
		sprite_gamepause_bg.setPosition(0, 0);
		window.draw(sprite_gamepause_bg);

		// for draw pause button
		if (pause_continue.is_normal) {
			pause_continue.sprite_normal.setPosition(230, 293);
			window.draw(pause_continue.sprite_normal);
		}
		else if (pause_continue.is_hover) {
			pause_continue.sprite_hover.setPosition(217, 283);
			window.draw(pause_continue.sprite_hover);
		}
		else if (pause_continue.is_down) {
			pause_continue.sprite_down.setPosition(236, 297);
			window.draw(pause_continue.sprite_down);
		}
		// for draw pause button
		if (pause_info.is_normal) {
			pause_info.sprite_normal.setPosition(176, 368);
			window.draw(pause_info.sprite_normal);
		}
		else if (pause_info.is_hover) {
			pause_info.sprite_hover.setPosition(156, 361);
			window.draw(pause_info.sprite_hover);
		}
		else if (pause_info.is_down) {
			pause_info.sprite_down.setPosition(188, 371);
			window.draw(pause_info.sprite_down);
		}
		// for draw pause button
		if (pause_return_menu.is_normal) {
			pause_return_menu.sprite_normal.setPosition(152, 436);
			window.draw(pause_return_menu.sprite_normal);
		}
		else if (pause_return_menu.is_hover) {
			pause_return_menu.sprite_hover.setPosition(131,428);
			window.draw(pause_return_menu.sprite_hover);
		}
		else if (pause_return_menu.is_down) {
			pause_return_menu.sprite_down.setPosition(165, 439);
			window.draw(pause_return_menu.sprite_down);
		}

	}

	if (gameover) {
		if (gameover_state == 0) {  // show lose surface
			sprite_gameover_bg_bad.setPosition(0, 0);
			window.draw(sprite_gameover_bg_bad);
		}
		else if (gameover_state == 1) {  // show win surface
			sprite_gameover_bg_good.setPosition(0, 0);
			window.draw(sprite_gameover_bg_good);
		}
		/// for draw return button
		if (return_menu.is_normal) {
			return_menu.sprite_normal.setPosition(820, 300);
			window.draw(return_menu.sprite_normal);
		}
		else if (return_menu.is_hover) {
			return_menu.sprite_hover.setPosition(800, 280);
			window.draw(return_menu.sprite_hover);
		}
		else if (return_menu.is_down) {
			return_menu.sprite_down.setPosition(820, 300);
			window.draw(return_menu.sprite_down);
		}
		if (game_model == single_player) {

			int dx = 0;
			Font text_font;
			Text text;
			Load_Font(text_font, text, "font/禹卫书法行书简体.ttf");
			text.setCharacterSize(30);
			text.setFillColor(Color(255, 255, 255, 255));
			text.setStyle(Text::Bold);

			text.setPosition(55, 340 + dx * 35);
			wstring each_line = L"人类玩家杀敌：";
			std::stringstream temp_str;
			temp_str << Human.killing_number;
			each_line = each_line + temp_str.str();
			text.setString(each_line);
			window.draw(text);
			dx++;

			for (int i = 0; i < machine_number; i++) {
				temp_str.str("");
				text.setPosition(65, 340 + dx * 35);
				wstring each_line = L"电脑-";
				temp_str << i + 1;
				each_line = each_line + temp_str.str() + L"杀敌：";
				temp_str.str("");
				temp_str << Machine[i].killing_number;
				each_line = each_line + temp_str.str();
				text.setString(each_line);
				window.draw(text);
				dx++;
			}
		}

	}

	window.display();
}

void Game::Draw_Text_Console() {
	RectangleShape rect(Vector2f(330,230)); // draw rectangle
	rect.setFillColor(Color(0, 0, 0, 100));
	rect.setPosition(700, 60);
	window.draw(rect);
	// when message amount is out of 15 ,then delete previous message in case the latest message is overflow
	while (message_amount > 15) {
		Delete_Message();
	}
	// show each message in message box
	Message_Box ptr = message->next;
	int dx = 0;
	Font text_font;
	Text text;
	Load_Font(text_font, text, "font/simsun.ttc");
	while (ptr) {
		text.setCharacterSize(15);
		text.setFillColor(Color(255, 255, 255, 255));
		text.setStyle(Text::Bold);
		text.setPosition(705, 60+dx*15);
		wstring each_line = L"";
		each_line = each_line + ptr->single_message;
		text.setString(each_line);
		window.draw(text);
		dx++;
		ptr = ptr->next;
	}
}

void Game::Draw_Discard_Pile() {
	Single_Card* ptr = discard_pile.Pile_Card_Total->next;
	int start_draw = 1;
	if (discard_pile.Pile_Card_Amount - start_draw > 6) {
		Load_Image(texture_discard_pile, sprite_discard_pile, "image/back_stable/pile_back.png");
		sprite_discard_pile.setPosition(window_width / 2, 300);
		window.draw(sprite_discard_pile);
	}
	while (discard_pile.Pile_Card_Amount - start_draw > 6) {
		start_draw++;
		ptr = ptr->next;
	}
	int dx = 1;
	while (ptr) {
		switch (ptr->card_info.single_card_number)
		{
		case kill:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/0.jpg");
			break;
		case jink:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/1.jpg");
			break;
		case analeptic:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/2.jpg");
			break;
		case peach:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/3.jpg");
			break;
		case amazing_grace:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/4.jpg");
			break;
		case archery_attack:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/5.jpg");
			break;
		default:
			break;
		}
		sprite_discard_pile.setPosition(window_width / 2 + dx * 15, 300);
		window.draw(sprite_discard_pile);
		dx++;
		ptr = ptr->next;
	}
}

void Game::Draw_HumanPlayer_Button() {
	//--->> judge which kind of state of button
	if (button_cancel.is_disabled) {
		button_cancel.sprite_disabled.setPosition(807, 694);
		window.draw(button_cancel.sprite_disabled);
	}
	else if (button_cancel.is_hover) {
		button_cancel.sprite_hover.setPosition(807, 694);
		window.draw(button_cancel.sprite_hover);
	}
	else if (button_cancel.is_down) {
		button_cancel.sprite_down.setPosition(807, 694);
		window.draw(button_cancel.sprite_down);
	}
	else if (button_cancel.is_normal) {
		button_cancel.sprite_normal.setPosition(807, 694);
		window.draw(button_cancel.sprite_normal);
	}
	if (button_discard.is_disabled) {
		button_discard.sprite_disabled.setPosition(874, 644);
		window.draw(button_discard.sprite_disabled);
	}
	else if (button_discard.is_hover) {
		button_discard.sprite_hover.setPosition(874, 644);
		window.draw(button_discard.sprite_hover);
	}
	else if (button_discard.is_down) {
		button_discard.sprite_down.setPosition(874, 644);
		window.draw(button_discard.sprite_down);
	}
	else if (button_discard.is_normal) {
		button_discard.sprite_normal.setPosition(874, 644);
		window.draw(button_discard.sprite_normal);
	}
	if (button_ok.is_disabled) {
		button_ok.sprite_disabled.setPosition(807, 604);
		window.draw(button_ok.sprite_disabled);
	}
	else if (button_ok.is_hover) {
		button_ok.sprite_hover.setPosition(807, 604);
		window.draw(button_ok.sprite_hover);
	}
	else if (button_ok.is_down) {
		button_ok.sprite_down.setPosition(807, 604);
		window.draw(button_ok.sprite_down);
	}
	else if (button_ok.is_normal) {
		button_ok.sprite_normal.setPosition(807, 604);
		window.draw(button_ok.sprite_normal);
	}
}
void Game::Draw_HumanPlayer() {
	// draw human_player_card
	Single_Card* ptr = Human.cards.Pile_Card_Total->next;
	for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {  // each card:  width 93 || height 130
		if (ptr->mouse_select_card) {
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 170;
			ptr->point_two.x = 165 + (i + 1) * 93;  
			ptr->point_two.y = window_height - 170 + 130;
			ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(ptr->sprite_card);
		}
		else if (ptr->enable_to_play == false || Human.gamestate==discard_phase) {
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 135;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 135 + 130;
			ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(ptr->sprite_card);

			RectangleShape rect(Vector2f(93, 130)); // draw rectangle
			rect.setFillColor(Color(0, 0, 0, 100));
			rect.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(rect);
		}
		else {
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 135;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 135 + 130;
			ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(ptr->sprite_card);
		}
		//window.draw(ptr->sprite_card);
		ptr = ptr->next;
	}
	Draw_HumanPlayer_Button();
	// draw Human HP
	for (int i = 0; i < Human.HP; i++) {
		sprite_Human_HP.setPosition(918 + i * 22, window_height - 166);  // the width of image named green big is 23
		window.draw(sprite_Human_HP);
	}
	// draw remained note
	if (Human.round_discard_phase) {
		if (Human.cards.Pile_Card_Amount - Human.HP > Human.selecet_card_amount) {

			RectangleShape rect(Vector2f(180, 30)); // draw rectangle
			rect.setFillColor(Color(0, 0, 0, 100));
			rect.setPosition(370, 500);
			window.draw(rect);

			Font reminded_note_font;
			Text reminded_note;
			Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
			reminded_note.setCharacterSize(20);
			reminded_note.setFillColor(Color(255, 255, 255, 255));
			reminded_note.setStyle(Text::Bold);
			reminded_note.setPosition(370, 500);
			wstring reminded = L"请弃置";
			std::stringstream temp_string;
			temp_string << Human.cards.Pile_Card_Amount - Human.HP;
			reminded = reminded + temp_string.str() + L"张牌";

			reminded_note.setString(reminded);
			window.draw(reminded_note);
		}
	}
	// draw dying state

	if (Human.is_dying == true && Human.die == false) {
		sprite_Human_save_me.setPosition(500, 530);
		window.draw(sprite_Human_save_me);
	}
}
void Game::Draw_Animator_Single(int set_frame, bool& animator, int& animator_counter, string file, int limited, int _x, int _y) {
	window.setFramerateLimit(set_frame);
	Texture texture_temp;
	Sprite sprite_temp;
	stringstream ss;
	ss << file << animator_counter << ".png";
	Load_Image(texture_temp, sprite_temp, ss.str(), 0, 0, 1, 1);
	sprite_temp.setPosition(_x, _y);
	if(!gamepause) animator_counter++;
	window.draw(sprite_temp);
	if (animator_counter == limited) {
		animator = false;
		animator_running = false;
		window.setFramerateLimit(60);
	}
}

void Game::Draw_Animator_Machine(Player& Machine) {
	if (Machine.animator_kill) { Draw_Animator_Single(16, Machine.animator_kill, Machine.animator_kill_counter, "image/animator/killer/", 13, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_jink) { Draw_Animator_Single(16, Machine.animator_jink, Machine.animator_jink_counter, "image/animator/jink/", 12, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_peach) { Draw_Animator_Single(16, Machine.animator_peach, Machine.animator_peach_counter, "image/animator/peach/", 17, Machine.location_two.x - 150, Machine.location_two.y - 50); }
	else if (Machine.animator_analeptic) { Draw_Animator_Single(16, Machine.animator_analeptic, Machine.animator_analeptic_counter, "image/animator/analeptic/", 17, Machine.location_two.x - 150, Machine.location_two.y - 50); }
	else if (Machine.animator_damage) { Draw_Animator_Single(22, Machine.animator_damage, Machine.animator_damage_counter, "image/animator/damage/", 6, Machine.location_one.x, Machine.location_one.y); }
}
void Game::Draw_Animator_Human() {
	if (Human.animator_kill) { Draw_Animator_Single(16, Human.animator_kill, Human.animator_kill_counter, "image/animator/killer/", 13, 500, 470); }
	else if (Human.animator_jink) { Draw_Animator_Single(16, Human.animator_jink, Human.animator_jink_counter, "image/animator/jink/", 12, 500, 470); }
	else if (Human.animator_peach) { Draw_Animator_Single(16, Human.animator_peach, Human.animator_peach_counter, "image/animator/peach/", 17, 500, 340); }
	else if (Human.animator_analeptic) { Draw_Animator_Single(16, Human.animator_analeptic, Human.animator_analeptic_counter, "image/animator/analeptic/", 17, 500, 380); }
	else if (Human.animator_damage) { Draw_Animator_Single(22, Human.animator_damage, Human.animator_damage_counter, "image/animator/damage/", 6, 910, window_height - 170); }
}
void Game::Draw_Machine(Player& Machine) {

	// draw Machine backboard & info
	sprite_npcboard.setPosition(Machine.location_one.x, Machine.location_one.y); // 宽 143 || 高 195
	window.draw(sprite_npcboard);
	// draw npc cards board
	sprite_npc_cards.setPosition(Machine.location_one.x, Machine.location_one.y + 60); // 宽 143 || 高 195
	window.draw(sprite_npc_cards);


	// draw Machine name info
	Font _font;
	Text machine_name;
	Load_Font(_font, machine_name, "font/simsun.ttc");
	machine_name.setCharacterSize(20);
	machine_name.setFillColor(Color(255, 255, 255, 255));
	machine_name.setStyle(Text::Bold);
	machine_name.setPosition(Machine.location_one.x + 30, Machine.location_one.y + 70);
	if (Machine.gamestate == die) {
		machine_name.setString(string_to_wstring("已阵亡....."));
	}
	else {
		machine_name.setString(string_to_wstring(Machine.player_name));
	}
	window.draw(machine_name);

	

	// draw npc card-number
	Font reminded_note_font;
	Text reminded_note;
	Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
	reminded_note.setCharacterSize(20);
	reminded_note.setFillColor(Color(0, 0, 0, 255));
	reminded_note.setStyle(Text::Bold);
	reminded_note.setPosition(Machine.location_one.x + 5, Machine.location_one.y + 60);
	wstring reminded;
	std::stringstream temp_string;
	temp_string << Machine.cards.Pile_Card_Amount;
	reminded = reminded + temp_string.str();

	reminded_note.setString(reminded);
	window.draw(reminded_note);

	// draw Machine HP
	for (int i = 0; i < Machine.HP; i++) {
		sprite_Machine_HP.setPosition(Machine.location_one.x + 18 + 14 * i, Machine.location_one.y + 30);  // the width of image named green small is 14
		window.draw(sprite_Machine_HP);
	}

	if (Machine.being_choose) {
		sprite_being_chosen.setPosition(Machine.location_one.x, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(sprite_being_chosen);
	}
	// draw machine round state
	if (Machine.round_draw_phase) {
		Machine.sprite_draw_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_draw_phase);
	}
	else if (Machine.round_play_phase) {
		Machine.sprite_play_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_play_phase);
	}
	else if (Machine.round_discard_phase) {
		Machine.sprite_discard_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_discard_phase);
	}
	else if (Machine.is_dying) {
		Machine.sprite_sos_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_sos_phase);
	}
	else if (exturn == Machine.charactor_code || Machine.round_defense) {
		Machine.sprite_response_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_response_phase);
	}
}
void Game::Draw_Stable_Background() {
	// draw background
	if (change_bg) {
		stringstream ss;
		ss << "image/back_stable/background-cover" << img_bg_number << ".jpg";
		Load_Image(texture_background, sprite_background, ss.str(), 0, 0, 1, 1);
		change_bg = false;
	}
	sprite_background.setPosition(0, 0);  // 宽 1140 || 高 770
	window.draw(sprite_background);
	// draw player equipment board
	sprite_player_equip_board.setPosition(0, window_height - 170);//宽 164 || 高 170
	window.draw(sprite_player_equip_board);
	// draw player hand-cards board
	sprite_player_hand_board.setPosition(164, window_height - 170);//宽 764 || 高 170
	window.draw(sprite_player_hand_board);
	// draw player button background
	sprite_player_button_background.setPosition(804, window_height - 168);//宽 106 || 高 168
	window.draw(sprite_player_button_background);
	// draw player general & role board
	sprite_player_role_background.setPosition(910, window_height - 170); // 宽 125 || 高 170
	window.draw(sprite_player_role_background);

	// draw piles & cards background
	sprite_piles_back.setPosition(window_width / 3, 300); // 宽 93 || 高 130
	window.draw(sprite_piles_back);

	if (game_model == single_player) {	
		// draw killing enemy note
		RectangleShape rect(Vector2f(140, 30)); // draw rectangle
		rect.setFillColor(Color(0, 0, 0, 100));
		rect.setPosition(800, 20);
		window.draw(rect);

		Font reminded_note_font;
		Text reminded_note;
		Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
		reminded_note.setCharacterSize(20);
		reminded_note.setFillColor(Color(255, 255, 255, 255));
		reminded_note.setStyle(Text::Bold);

		// show killing time 
		wstring reminded = L"已杀敌：";
		std::stringstream temp_string;
		temp_string << Human.killing_number;
		reminded = reminded + temp_string.str();
		reminded_note.setString(reminded);
		reminded_note.setPosition(810, 20);
		window.draw(reminded_note);

		// show piles amount
		reminded = L"摸牌堆牌数：";
		temp_string.str("");
		temp_string << piles.Pile_Card_Amount;
		reminded = reminded + temp_string.str();

		reminded_note.setString(reminded);
		reminded_note.setPosition(350, 450);
		window.draw(reminded_note);

		// show discard piles amount
		reminded = L"弃牌堆牌数：";
		temp_string.str("");
		temp_string << discard_pile.Pile_Card_Amount;
		reminded = reminded + temp_string.str();

		reminded_note.setString(reminded);
		reminded_note.setPosition(550, 450);
		window.draw(reminded_note);
	}
}