#include "common/Game.h"

// std::ostream& bold_on(std::ostream& os) { return os << "\033[1m"; }
// std::ostream& bold_off(std::ostream& os) { return os << "\033[0m"; }

bool running = true;

// function declare
inline bool file_exists(const std::string& name);
wstring string_to_wstring(string str);
void display_incoming(bool* running, Game* game, sf::TcpSocket* server, std::string* filter_name);
void display_incoming(bool* running, Game* game, sf::TcpSocket* server, std::string* filter_name);
void update_class(Player &player,sf::Packet in_packet,Game &game);
LPCWSTR string_To_LPCWSTR(string _string);
void Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY);

// change string to lpcwstr so that string can display on warning windows
LPCWSTR string_To_LPCWSTR(string _string) {
	size_t origsize = _string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* _LPCWSTR = (wchar_t*)malloc(sizeof(wchar_t) * (_string.length() - 1));
	mbstowcs_s(&convertedChars, _LPCWSTR, origsize, _string.c_str(), _TRUNCATE);
	return _LPCWSTR;
}
// load image
void Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY) {
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

inline bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

inline void send_packet(const std::string type, const std::string name,const std::string body, sf::TcpSocket* socket) {
	sf::Packet pack;
	pack << type << name << body;
	socket->send(pack);
}

wstring string_to_wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

void update_class(Player & player, sf::Packet in_packet, Game& game) {
	int update_type;
	in_packet >> update_type;
	switch (update_type)
	{
	case Msg:
		break;
	case NAME:
		in_packet >> player.player_name;
		break;
	case Card_Number :
		in_packet >> player.cards.Pile_Card_Amount;
		break;
	case Limit_Hp:
		in_packet >> player.limited_HP;
		break;
	case Hp:
		in_packet >> player.HP;
		break;
	case Card_Sequence: {
		int judge;
		in_packet >> judge;
		if (judge == -1) {
			player.cards.clear();
		}
		else if (judge == -2) {
			break;
		}
		else if (judge==-3)	{  // card empty
			player.cards.clear();
		}
		else {
			player.cards.Insert_Card(judge, 1);
			player.cards.Get_Node(player.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			Single_Card* ptr = player.cards.Pile_Card_Total->next;
			for (int i = 0; i < player.cards.Pile_Card_Amount; i++) {
				if (!ptr->file_loaded) {
					stringstream ss;
					ss << "image/skill&equip_card/small_card/" << ptr->card_info.single_card_number << ".jpg";
					Load_Image(ptr->texture_card, ptr->sprite_card, ss.str(), 0, 0, 1, 1);
					ptr->file_loaded = true;
				}
				ptr->enable_to_play = false;
				ptr = ptr->next;
			}
		}
	}break;
	case Turn_State: {
		int state_code;
		in_packet >> state_code;
		player.round_draw_phase = false;
		player.round_play_phase = false;
		player.round_discard_phase = false;
		player.round_defense = false;
		player.is_dying = false;
		player.die = false;
		player.gamestate = state_code;
		switch (state_code)
		{
		case none:break;
		case draw_phase:
			player.round_draw_phase = true;
			break;
		case play_phase:
			player.round_play_phase = true;
			break;
		case discard_phase:
			player.round_discard_phase = true;
			break;
		case defense_phase:
			player.round_defense = true;
			break;
		case dying_phase:
			player.is_dying = true;
			break;
		case die:
			player.die = true; 
			break;
		}
	}break;
	case Animation: {
		string animator;
		in_packet >> animator;
		game.animator_running = true;
		cout << "yet::::::" << animator << endl;
		if (animator == "kill") {
			player.animator_kill = true;
			player.animator_kill_counter = 0;
		}
		else if (animator == "jink") {
			player.animator_jink = true;
			player.animator_jink_counter = 0;
		}
		else if (animator == "peach") {
			player.animator_peach = true;
			player.animator_peach_counter = 0;
		}
		else if (animator == "analeptic") {
			player.animator_analeptic = true;
			player.animator_analeptic_counter = 0;
		}
		else if (animator == "damage") {
			player.animator_damage = true;
			player.animator_damage_counter = 0;
		}
	}break;
	case Defense_State:{
			if (player.is_Mechine == false) {
				string skill_type;
				in_packet >> skill_type;
				if (skill_type == "kill") player.skill.need_jink = true;
				if (skill_type == "analeptic_kill") player.skill.defense_analeptic_kill = true;
				if (skill_type == "begging_peach") player.skill.begging_peach = true;
				if (skill_type == "self_save") player.self_save = true;
			}
		}break;
	default:
		break;
	}
}

/*---------------using---in------MSG------receive------------*/
void display_incoming(bool* running,  Game* game, sf::TcpSocket* server, std::string* filter_name) {
	while (running) {
		sf::Packet in_packet;
		if (server->receive(in_packet) == sf::Socket::Done) {
			std::string type;
			in_packet >> type ;
			if (type == "MSG") {
				string name, body;
				in_packet >> name >> body;
				if (name == *filter_name) continue;
				std::cout << bold_on << name << ": " << bold_off << body << std::endl;
			}
			else if (type == "DISCON") {
				string name, body;
				in_packet >> name >> body;
				std::cout << bold_on << "** " << name << bold_off << " left the server! (Reason: " << body << ")" << std::endl;
			}
			if (type == (*game).Human.player_name) {
				int code=-1;
				int location_code;
				in_packet >> code;

				wstring enter_player;
				string enter_player_name;


				switch (code)
				{
				case enter_room: {
					in_packet >> enter_player_name;
					enter_player = string_to_wstring(enter_player_name) + L" 进入房间！";
					(*game).Insert_Message(enter_player);
				}break;
				case game_start: {
					(*game).Insert_Message(L" **  游 戏 开 始 **");
				}break;
				case set_location_code:	{
					in_packet >> (*game).Human.location_code;
					cout << (*game).Human.player_name << "的 location-code 为" << (*game).Human.location_code << endl;
					switch ((*game).machine_number)
					{
					case 1: {
						switch ((*game).Human.location_code)
						{
						case 0:
							(*game).Machine[0].location_code = 1;
							break;
						case 1:
							(*game).Machine[0].location_code = 0;
							break;
						}
						break;
					}
					case 2: {
						switch ((*game).Human.location_code)
						{
						case 0:
							(*game).Machine[0].location_code = 1;
							(*game).Machine[1].location_code = 2;
							break;
						case 1:
							(*game).Machine[0].location_code = 2;
							(*game).Machine[1].location_code = 0;
							break;
						case 2:
							(*game).Machine[0].location_code = 0;
							(*game).Machine[1].location_code = 1;
							break;
						}
						break;
					}
					case 3: {
						switch ((*game).Human.location_code)
						{
						case 0:
							(*game).Machine[0].location_code = 1;
							(*game).Machine[1].location_code = 2;
							(*game).Machine[2].location_code = 3;
							break;
						case 1:
							(*game).Machine[0].location_code = 2;
							(*game).Machine[1].location_code = 3;
							(*game).Machine[2].location_code = 0;
							break;
						case 2:
							(*game).Machine[0].location_code = 3;
							(*game).Machine[1].location_code = 0;
							(*game).Machine[2].location_code = 1;
							break;
						case 3:
							(*game).Machine[0].location_code = 0;
							(*game).Machine[1].location_code = 1;
							(*game).Machine[2].location_code = 2;
							break;
						}
						break;
					}
					case 4: {
						switch ((*game).Human.location_code)
						{
						case 0:
							(*game).Machine[0].location_code = 1;
							(*game).Machine[1].location_code = 2;
							(*game).Machine[2].location_code = 3;
							(*game).Machine[3].location_code = 4;
							break;
						case 1:
							(*game).Machine[0].location_code = 2;
							(*game).Machine[1].location_code = 3;
							(*game).Machine[2].location_code = 4;
							(*game).Machine[3].location_code = 0;
							break;
						case 2:
							(*game).Machine[0].location_code = 3;
							(*game).Machine[1].location_code = 4;
							(*game).Machine[2].location_code = 0;
							(*game).Machine[3].location_code = 1;
							break;
						case 3:
							(*game).Machine[0].location_code = 4;
							(*game).Machine[1].location_code = 0;
							(*game).Machine[2].location_code = 1;
							(*game).Machine[3].location_code = 2;
							break;
						case 4:
							(*game).Machine[0].location_code = 0;
							(*game).Machine[1].location_code = 1;
							(*game).Machine[2].location_code = 2;
							(*game).Machine[3].location_code = 3;
							break;
						}
						break;
					}
					}
				}break;
				case update_info: {
					in_packet >> location_code;
					if (location_code == (*game).Human.location_code) {
						update_class((*game).Human, in_packet,*game);
					}
					else if (location_code == (*game).Machine[0].location_code) {
						update_class((*game).Machine[0], in_packet, *game);
					}
					else if (location_code == (*game).Machine[1].location_code) {
						update_class((*game).Machine[1], in_packet, *game);
					}
					else if (location_code == (*game).Machine[2].location_code) {
						update_class((*game).Machine[2], in_packet, *game);
					}
					else if (location_code == (*game).Machine[3].location_code) {
						update_class((*game).Machine[3], in_packet, *game);
					}
				}break;
				default:
					break;
				}
			}
		}
	}
}
int main(int argc, char* argv[]) {

	Game SGS;

	SGS.connection();

	std::thread display_thread(display_incoming, &running, &SGS, &SGS.socket, &SGS.name);

    std::cout<<std::string(10, '_') << std::endl << std::endl;

	SGS.Game_Run();

	running = false;
	display_thread.join();


}
