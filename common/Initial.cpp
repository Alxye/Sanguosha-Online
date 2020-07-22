#include "Game.h"

Game::Game() {
	window_width = 1035;
	window_height = 770;
	virtual_vector.x = -999;
	virtual_vector.y = -999;
	human_defense = false;
	animator_running = false;
	window.create(sf::VideoMode(window_width, window_height), L"三国杀_BY_赵茜茜", sf::Style::Close);
    // initialize message box
	message = new Message;
	message->next = NULL;
	message_amount = 0;
	// music-play
	Load_Music(music_bg, "audio/bg.ogg");
	sound_volume = 20;
	// initialize game mode for single or muti; default one is -1
	game_model = -1;

	// change player type
	Human.is_Mechine = false;
	for (int i=0;i<4;i++){
		Machine[i].is_Mechine = true;
	}
}

void Game::Initial() {
	// initialize game state
	gamestart = true;
	gameover = false;
	gamequit = false;
	gamerun = false;
	gamechoose = false;
	net_chosen = false;
	gamepause = false;
	gameinfo = false;
	restart = false;
	// set gameover state value to default
	gameover_state = -1;
	// set style mode
	globe_style_mode = 0;    // default is 0--light,1--dark
	gamestart_style=0;
	gameinfo_style=0;
	gamechoose_style=0;
	// initialize background number
	img_bg_number = 0;

	round_loop_starter = -1;
	// dying round loop
	dying_loop = false;
	// amazing grace round loop
	amazing_grace_loop = false;
	archery_attack_loop = false;

	// load background(default)
	Load_Image(texture_background, sprite_background, "image/back_stable/background-cover0.jpg", 0, 0, 1, 1);                  
	// load equipment background in player's interface
	Load_Image(texture_player_equip_board, sprite_player_equip_board, "image/back_stable/playerboard-equip.png");
	// load hand background in player's interface
	Load_Image(texture_player_hand_board, sprite_player_hand_board, "image/back_stable/playerboard-hand.png");
	// load button container in player's interface
	Load_Image(texture_player_button_background, sprite_player_button_background, "image/back_stable/playerbutton_background.png");
	// load player's information in player's interface
	Load_Image(texture_player_role_background, sprite_player_role_background, "image/back_stable/playerboard-role.png");
	// load npc's interface
	Load_Image(texture_npcboard, sprite_npcboard, "image/back_stable/npcboard.png");
	Load_Image(texture_npc_cards, sprite_npc_cards, "image/back_stable/handcard.png");
	Load_Image(texture_piles_back, sprite_piles_back, "image/back_stable/pile_back.png");
	// load npc_being chosen
	Load_Image(texture_being_chosen, sprite_being_chosen, "image/back_stable/sos.png", 0, 0, 1, 1);
	// load button 
	//---->> cancel button
	Load_Image(button_cancel.texture_disabled, button_cancel.sprite_disabled, "image/back_stable/button/cancel-disabled.png", 0, 0, 1, 1);
	Load_Image(button_cancel.texture_down, button_cancel.sprite_down, "image/back_stable/button/cancel-down.png", 0, 0, 1, 1);
	Load_Image(button_cancel.texture_hover, button_cancel.sprite_hover, "image/back_stable/button/cancel-hover.png", 0, 0, 1, 1);
	Load_Image(button_cancel.texture_normal, button_cancel.sprite_normal, "image/back_stable/button/cancel-normal.png", 0, 0, 1, 1);
	//---->> discard button
	Load_Image(button_discard.texture_disabled, button_discard.sprite_disabled, "image/back_stable/button/discard-disabled.png", 0, 0, 1, 1);
	Load_Image(button_discard.texture_down, button_discard.sprite_down, "image/back_stable/button/discard-down.png", 0, 0, 1, 1);
	Load_Image(button_discard.texture_hover, button_discard.sprite_hover, "image/back_stable/button/discard-hover.png", 0, 0, 1, 1);
	Load_Image(button_discard.texture_normal, button_discard.sprite_normal, "image/back_stable/button/discard-normal.png", 0, 0, 1, 1);
	//---->> assure button
	Load_Image(button_ok.texture_disabled, button_ok.sprite_disabled, "image/back_stable/button/ok-disabled.png", 0, 0, 1, 1);
	Load_Image(button_ok.texture_down, button_ok.sprite_down, "image/back_stable/button/ok-down.png", 0, 0, 1, 1);
	Load_Image(button_ok.texture_hover, button_ok.sprite_hover, "image/back_stable/button/ok-hover.png", 0, 0, 1, 1);
	Load_Image(button_ok.texture_normal, button_ok.sprite_normal, "image/back_stable/button/ok-normal.png", 0, 0, 1, 1);
	//---->> Human & Machine Player HP
	Load_Image(texture_Human_HP, sprite_Human_HP, "image/HP/green_big.png", 0, 0, 1, 1);
	Load_Image(texture_Machine_HP, sprite_Machine_HP, "image/HP/green_small.png", 0, 0, 1, 1);
	//---->> Human's dying state saving me
	Load_Image(texture_Human_save_me, sprite_Human_save_me, "image/gameover/save-me.png", 0, 0, 1, 1);
	//---->> Phase mask border for machine
	for (int number = 0; number < 4; number++) {
		Load_Image(Machine[number].texture_draw_phase, Machine[number].sprite_draw_phase, "image/phase/draw.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_play_phase, Machine[number].sprite_play_phase, "image/phase/play.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_discard_phase, Machine[number].sprite_discard_phase, "image/phase/discard.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_judge_phase, Machine[number].sprite_judge_phase, "image/phase/judge.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_response_phase, Machine[number].sprite_response_phase, "image/phase/response.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_sos_phase, Machine[number].sprite_sos_phase, "image/phase/sos.png", 0, 0, 1, 1);
	}
	Load_Image(texture_Human_save_me, sprite_Human_save_me, "image/gameover/save-me.png", 0, 0, 1, 1);

	//---->> START surface image loading (default image)
	Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_light.png", 0, 0, 1, 1);
	//---->> START button enable & texture,sprite tied
    // normal (default is mode ==0)
	Load_Image(gamestart_go.texture_normal, gamestart_go.sprite_normal, "image/back_stable/start-surface/start-dark-button-go.png", 0, 0, 1, 1);
	Load_Image(gamestart_info.texture_normal, gamestart_info.sprite_normal, "image/back_stable/start-surface/start-dark-button-info.png", 0, 0, 1, 1);
	Load_Image(gamestart_quit.texture_normal, gamestart_quit.sprite_normal, "image/back_stable/start-surface/start-dark-button-quit.png", 0, 0, 1, 1);
    // high light (default is mode ==0)
	Load_Image(gamestart_go.texture_hover, gamestart_go.sprite_hover, "image/back_stable/start-surface/start-light-button-go.png", 0, 0, 1, 1);
	Load_Image(gamestart_info.texture_hover, gamestart_info.sprite_hover, "image/back_stable/start-surface/start-light-button-info.png", 0, 0, 1, 1);
	Load_Image(gamestart_quit.texture_hover, gamestart_quit.sprite_hover, "image/back_stable/start-surface/start-light-button-quit.png", 0, 0, 1, 1);
	// down
	Load_Image(gamestart_go.texture_down, gamestart_go.sprite_down, "image/back_stable/start-surface/start-button-go-down.png", 0, 0, 1, 1);
	Load_Image(gamestart_info.texture_down, gamestart_info.sprite_down, "image/back_stable/start-surface/start-button-info-down.png", 0, 0, 1, 1);
	Load_Image(gamestart_quit.texture_down, gamestart_quit.sprite_down, "image/back_stable/start-surface/start-button-quit-down.png", 0, 0, 1, 1);

	// enable button state
	//---->> for game start
	gamestart_go.enable_normal_button();
	gamestart_info.enable_normal_button();
	gamestart_quit.enable_normal_button();
	//---->> for game info
	gameinfo_thanks.enable_normal_button();
	gameinfo_gameinfo.enable_normal_button();
	gameinfo_phaseinfo.enable_normal_button();
	gameinfo_cardinfo.enable_normal_button();
	//---->> GAME INFO surface image loading (default image)
	Load_Image(texture_gameinfo_bg, sprite_gameinfo_bg, "image/back_stable/info-surface/bg-light.png", 0, 0, 1, 1);
	//---->> GAME INFO button enable & texture,sprite tied
	// normal (default is mode ==0)
	Load_Image(gameinfo_thanks.texture_normal, gameinfo_thanks.sprite_normal, "image/back_stable/info-surface/thanksinfo-button-light.png", 0, 0, 1, 1);
	Load_Image(gameinfo_gameinfo.texture_normal, gameinfo_gameinfo.sprite_normal, "image/back_stable/info-surface/gameinfo-button-light.png", 0, 0, 1, 1);
	Load_Image(gameinfo_phaseinfo.texture_normal, gameinfo_phaseinfo.sprite_normal, "image/back_stable/info-surface/phaseinfo-button-light.png", 0, 0, 1, 1);
	Load_Image(gameinfo_cardinfo.texture_normal, gameinfo_cardinfo.sprite_normal, "image/back_stable/info-surface/cardinfo-button-light.png", 0, 0, 1, 1);
	// high light (default is mode ==0)
	Load_Image(gameinfo_thanks.texture_hover, gameinfo_thanks.sprite_hover, "image/back_stable/info-surface/thanksinfo-button-dark.png", 0, 0, 1, 1);
	Load_Image(gameinfo_gameinfo.texture_hover, gameinfo_gameinfo.sprite_hover, "image/back_stable/info-surface/gameinfo-button-dark.png", 0, 0, 1, 1);
	Load_Image(gameinfo_phaseinfo.texture_hover, gameinfo_phaseinfo.sprite_hover, "image/back_stable/info-surface/phaseinfo-button-dark.png", 0, 0, 1, 1);
	Load_Image(gameinfo_cardinfo.texture_hover, gameinfo_cardinfo.sprite_hover, "image/back_stable/info-surface/cardinfo-button-dark.png", 0, 0, 1, 1);
	// down
	Load_Image(gameinfo_thanks.texture_down, gameinfo_thanks.sprite_down, "image/back_stable/info-surface/thanksinfo-button-dark.png", 0, 0, 1, 1);
	Load_Image(gameinfo_gameinfo.texture_down, gameinfo_gameinfo.sprite_down, "image/back_stable/info-surface/gameinfo-button-dark.png", 0, 0, 1, 1);
	Load_Image(gameinfo_phaseinfo.texture_down, gameinfo_phaseinfo.sprite_down, "image/back_stable/info-surface/phaseinfo-button-dark.png", 0, 0, 1, 1);
	Load_Image(gameinfo_cardinfo.texture_down, gameinfo_cardinfo.sprite_down, "image/back_stable/info-surface/cardinfo-button-dark.png", 0, 0, 1, 1);
	//---->> game info load word texture (default is 0===light)
	Load_Image(texture_gameinfo_thanks, sprite_gameinfo_thanks, "image/back_stable/info-surface/thanks-light.png", 0, 0, 1, 1);
	Load_Image(texture_gameinfo_gameinfo, sprite_gameinfo_gameinfo, "image/back_stable/info-surface/gameinfo-light.png", 0, 0, 1, 1);
	Load_Image(texture_gameinfo_phaseinfo, sprite_gameinfo_phaseinfo, "image/back_stable/info-surface/phaseinfo-light.png", 0, 0, 1, 1);
	Load_Image(texture_gameinfo_cardinfo, sprite_gameinfo_cardinfo, "image/back_stable/info-surface/cardinfo-light.png", 0, 0, 1, 1);
	//---->> return button initialize
	Load_Image(return_button.texture_normal, return_button.sprite_normal, "image/back_stable/info-surface/return-normal.png", 0, 0, 1, 1);
	Load_Image(return_button.texture_hover, return_button.sprite_hover, "image/back_stable/info-surface/return-hover.png", 0, 0, 1, 1);
	Load_Image(return_button.texture_down,return_button.sprite_down, "image/back_stable/info-surface/return-normal.png", 0, 0, 1, 1);
	return_button.enable_normal_button();

	//---->> game chosen load texture&sprite
	Load_Image(texture_gamechoose_contain, sprite_gamechoose_contain, "image/back_stable/chosen-surface/chosen-word-light.png", 0, 0, 1, 1);
	Load_Image(texture_netchoose_contain, sprite_netchoose_contain, "image/back_stable/chosen-surface/chosen-net-word-light.png", 0, 0, 1, 1);
	//---->> game chosen button initialize
	Load_Image(button_gamechoose.texture_hover, button_gamechoose.sprite_hover, "image/back_stable/chosen-surface/chosen-button-light.png", 0, 0, 1, 1);
	button_gamechoose.enable_normal_button();

	//---->> GAME-OVER load texture & sprite
	Load_Image(texture_gameover_bg_good, sprite_gameover_bg_good, "image/back_stable/over-surface/gameover-good.png", 0, 0, 1, 1);
	Load_Image(texture_gameover_bg_bad, sprite_gameover_bg_bad, "image/back_stable/over-surface/gameover-bad.png", 0, 0, 1, 1);
	Load_Image(return_menu.texture_normal, return_menu.sprite_normal, "image/back_stable/over-surface/返回主菜单-normal.png", 0, 0, 1, 1);
	Load_Image(return_menu.texture_hover, return_menu.sprite_hover, "image/back_stable/over-surface/返回主菜单-hover.png", 0, 0, 1, 1);
	Load_Image(return_menu.texture_down, return_menu.sprite_down, "image/back_stable/over-surface/返回主菜单-normal.png", 0, 0, 1, 1);
	return_menu.enable_normal_button();

	//---->> GAME-PAUSE button initialize
	Load_Image(pause_button.texture_normal, pause_button.sprite_normal, "image/back_stable/gamepause-button-normal.png", 0, 0, 1, 1);
	Load_Image(pause_button.texture_hover, pause_button.sprite_hover, "image/back_stable/gamepause-button-hover.png", 0, 0, 1, 1);
	Load_Image(pause_button.texture_down, pause_button.sprite_down, "image/back_stable/gamepause-button-normal.png", 0, 0, 1, 1);
	pause_button.enable_normal_button();

	//---->> GAME_PAUSE surface
	Load_Image(texture_gamepause_bg, sprite_gamepause_bg, "image/back_stable/pause-surface/pause-bg.png", 0, 0, 1, 1);
	Load_Image(pause_continue.texture_normal, pause_continue.sprite_normal, "image/back_stable/pause-surface/pause-continue-normal.png", 0, 0, 1, 1);
	Load_Image(pause_continue.texture_hover, pause_continue.sprite_hover, "image/back_stable/pause-surface/pause-continue-hover.png", 0, 0, 1, 1);
	Load_Image(pause_continue.texture_down, pause_continue.sprite_down, "image/back_stable/pause-surface/pause-continue-normal.png", 0, 0, 1, 1);
	Load_Image(pause_info.texture_normal, pause_info.sprite_normal, "image/back_stable/pause-surface/pause-info-normal.png", 0, 0, 1, 1);
	Load_Image(pause_info.texture_hover, pause_info.sprite_hover, "image/back_stable/pause-surface/pause-info-hover.png", 0, 0, 1, 1);
	Load_Image(pause_info.texture_down, pause_info.sprite_down, "image/back_stable/pause-surface/pause-info-normal.png", 0, 0, 1, 1);
	Load_Image(pause_return_menu.texture_normal, pause_return_menu.sprite_normal, "image/back_stable/pause-surface/pause-return-menu-normal.png", 0, 0, 1, 1);
	Load_Image(pause_return_menu.texture_hover, pause_return_menu.sprite_hover, "image/back_stable/pause-surface/pause-return-menu-hover.png", 0, 0, 1, 1);
	Load_Image(pause_return_menu.texture_down, pause_return_menu.sprite_down, "image/back_stable/pause-surface/pause-return-menu-normal.png", 0, 0, 1, 1);
	// initialize button
	pause_continue.enable_normal_button();
	pause_info.enable_normal_button();
	pause_return_menu.enable_normal_button();

	button_animate_count = 0;

	//---->> initialize charactor code to get catch of each member
	Human.charactor_code = human;
	Machine[0].charactor_code = machine_0;
	Machine[1].charactor_code = machine_1;
	Machine[2].charactor_code = machine_2;
	Machine[3].charactor_code = machine_3;
	//---->> initialize charactor location
	Human.location_one.x = -1;
	Human.location_one.y = -1;
	Human.location_two.x = -1;
	Human.location_two.y = -1;

	//---->> clear all card
	piles.clear();
	discard_pile.clear();
	temp_pile.clear();
	Human.cards.clear();
	Human.gamestate = none;
	Human.die = false;
	for (int i = 0; i < 4; i++) {
		Machine[i].cards.clear();
		Machine[i].gamestate = none;
		Machine[i].die = false;
	}

	//---->> diable all the button
	button_ok.enable_diabled_button();
	button_discard.enable_diabled_button();
	button_cancel.enable_diabled_button();

	// clear message
	while (message_amount) {
		Delete_Message();
	}
}

int Game::Previous_Draw_Phase() {
	Insert_Message(L">>游戏开局,每个玩家摸4张牌");
	// each machine get 4 cards
	for (int number = 0; number < machine_number; number++) {
		for (int i = 0; i < 4; i++) {
			Machine[number].cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		switch (number)
		{
		case 0:
			Insert_Message(L"电脑-1 摸了4张牌");
			break;
		case 1:
			Insert_Message(L"电脑-2 摸了4张牌");
			break;
		case 2:
			Insert_Message(L"电脑-3 摸了4张牌");
			break;
		case 3:
			Insert_Message(L"电脑-4 摸了4张牌");
			break;
		}
	}
	// human get 4 cards
	for (int i = 0; i < 4; i++) {
		Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
		Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
		piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
	}
	Insert_Message(L"人类玩家摸了4张牌");
	int first_hand = rand() % (machine_number)+1;
	switch (first_hand)
	{
	case human:
		Insert_Message(L"》》》人类玩家抽得先手出牌！");
		break;
	case machine_0:
		Insert_Message(L"》》》电脑-1 抽得先手出牌！");
		break;
	case machine_1:
		Insert_Message(L"》》》电脑-2 抽得先手出牌！");
		break;
	case machine_2:
		Insert_Message(L"》》》电脑-3 抽得先手出牌！");
		break;
	case machine_3:
		Insert_Message(L"》》》电脑-4 抽得先手出牌！");
		break;
	}
	return first_hand;  // the rand function would determine which one to play first
}

// change string to lpcwstr so that string can display on warning windows
LPCWSTR Game::string_To_LPCWSTR(string _string) {
	size_t origsize = _string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* _LPCWSTR = (wchar_t*)malloc(sizeof(wchar_t) * (_string.length() - 1));
	mbstowcs_s(&convertedChars, _LPCWSTR, origsize, _string.c_str(), _TRUNCATE);
	return _LPCWSTR;
}
// load image
void Game::Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY) {
	if (!texture.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , image is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Image(texture, sprite, filename, originX, originY, factorX, factorY);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		sprite.setTexture(texture);
		sprite.setOrigin(originX, originY);
		sprite.setScale(factorX, factorY);
	}
}
// for test to printout
void Game::out_put(Single_Card single) {
	cout << "出的卡牌：" << single.card_name << endl;
	cout << "卡牌号码：" << single.card_info.single_card_number << endl;
	cout << "卡牌花色：" << single.card_name << endl;
	cout << "卡牌能否攻击：" << single.card_info.can_attck << endl;
}
// load font & text

void Game::Load_Font(Font& font, Text& text, string filename) {
	if (!font.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , font is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Font(font, text, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		text.setFont(font);
	}
}

void Game::Load_Sound(Sound& sound, SoundBuffer& soundbuffer, string filename) {
	if (!soundbuffer.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , file is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Sound(sound,soundbuffer, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		sound.setVolume(50);
		sound.setBuffer(soundbuffer);
	}
}

void Game::Load_Music(Music& music, string filename) {
	if (!music.openFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , file is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Music(music, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		music.setVolume(20);
		music.play();
		music.setLoop(true);
	}
}