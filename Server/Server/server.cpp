#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <fstream>

#include "common/Game.h"

////////////////////////////// basic network connection  /////////////////////////
#define NET_MSG_SIZE 1024 // bytes
#define NET_PORT_DEFAULT 53000

inline bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

inline void send_packet(const std::string type, const std::string name,
	const std::string body, sf::TcpSocket* socket) {
	sf::Packet pack;
	pack << type << name << body;
	socket->send(pack);
}
////////////////////////////// basic network connection  /////////////////////////

class Queue
{
public:
	bool empty;
	bool full;
	bool game_start;
	Player p[5];
	int player_amount;   // including host player
	int current_player_amount;

	int current_turn;
	int turn_draw;
	int turn_play;
	int turn_discard;
	int turn_dying;
	int turn_extra;

	// for pile 

	Pile_Card current_pile;
	Pile_Card discard_pile;
	Pile_Card temp_pile;

	Queue() {
		empty = true;
		full = false;
		game_start = false;
		player_amount = 0;
		current_player_amount = 0;
		current_turn = -1; // default current turn is -1
		turn_draw = -1;
		turn_play = -1;
		turn_discard = -1;
		turn_extra = -1;
		for (int i = 0; i < 5; i++) {
			p[i].location_code = i;
			p[i].HP = 3;
			p[i].limited_HP = 3;
		}
	}
};

void update_class(std::list<sf::TcpSocket*> clients, Queue queue, int type) {
	for (int j = 0; j < queue.player_amount; j++) {

		switch (type)
		{
		case Msg: {

		}break;
		case NAME: {
			// update all player's name in each client
			for (int k = 0; k < queue.current_player_amount; k++) {

				sf::Packet packet;
				packet << queue.p[j].player_name << update_info;
				packet << k << NAME << queue.p[k].player_name;

				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					client.send(packet);
				}
			}
		}break;
		case Card_Number: {
			for (int k = 0; k < queue.current_player_amount; k++) {
				sf::Packet packet;
				packet << queue.p[j].player_name << update_info;
				packet << k << Card_Number << queue.p[k].cards.Pile_Card_Amount;
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					client.send(packet);
				}
			}
		}break;
		case Limit_Hp: {
			for (int k = 0; k < queue.current_player_amount; k++) {

				sf::Packet packet;
				packet << queue.p[j].player_name << update_info;
				packet << k << Limit_Hp << queue.p[k].limited_HP;
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					client.send(packet);
				}
			}
		}break;
		case Hp: {
			for (int k = 0; k < queue.current_player_amount; k++) {
				sf::Packet packet;
				packet << queue.p[j].player_name << update_info;
				packet << k << Hp << queue.p[k].HP;
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					client.send(packet);
				}
			}
		}break;
		case Card_Sequence: {
			for (int k = 0; k < queue.current_player_amount; k++) {
				Single_Card* ptr = queue.p[k].cards.Pile_Card_Total->next;
				if (ptr == NULL) {
					sf::Packet packet;
					packet << queue.p[j].player_name << update_info;
					packet << k << Card_Sequence << -3;   // -1 is mark to send begin
					for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
						sf::TcpSocket& client = **it;
						client.send(packet);
					}
				}
				if (ptr != NULL) {
					sf::Packet packet;
					packet << queue.p[j].player_name << update_info;
					packet << k << Card_Sequence << -1;   // -1 is mark to send begin
					for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
						sf::TcpSocket& client = **it;
						client.send(packet);
					}
				}
				while (ptr != NULL) {
					sf::Packet packet;
					packet << queue.p[j].player_name << update_info;
					packet << k << Card_Sequence << ptr->card_info.single_card_number;
					for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
						sf::TcpSocket& client = **it;
						client.send(packet);
					}
					ptr = ptr->next;
				}
				sf::Packet packet;
				packet << queue.p[j].player_name << update_info;
				packet << k << Card_Sequence << -2;  // -2 to mark card send end
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					client.send(packet);
				}
			}
		}break;
		case Turn_State: {
			for (int k = 0; k < queue.current_player_amount; k++) {
				sf::Packet packet;
				packet << queue.p[j].player_name << update_info;
				packet << k << Turn_State << queue.p[k].gamestate;
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					client.send(packet);
				}
			}
		}break;
		}
	}
}

int main(int argc, char* argv[]) {
	Queue queue[10];
	std::string motd;
	int port = NET_PORT_DEFAULT;
	bool motd_set = false;



	if (!motd_set) {
		if (file_exists("/etc/tserver/motd.txt")) {
			std::ifstream motdfile("/etc/tserver/motd.txt");
			motd = std::string((std::istreambuf_iterator<char>(motdfile)), std::istreambuf_iterator<char>());
		}
		else {
			std::cout << bold_on << "Type an Name" << bold_off << " (for server) to be displayed to any clients: ";
			std::getline(std::cin, motd);
		}
	}

	sf::TcpListener listener;
	listener.listen(port);

	std::cout << "Listening for clients...\n";

	std::list<sf::TcpSocket*> clients;
	std::map<sf::TcpSocket*, std::string> client2name;  // for sent message to other player
	sf::SocketSelector selector;

	selector.add(listener);

	while (true) {

		if (selector.wait()) {
			// if the listener is ready then a client's trying to connect
			if (selector.isReady(listener)) {
				sf::TcpSocket* new_client = new sf::TcpSocket;

				if (listener.accept(*new_client) == sf::Socket::Done) {

					clients.push_back(new_client);
					client2name[new_client] = new_client->getRemoteAddress().toString();
					selector.add(*new_client);
					std::cout << bold_on << "** " << bold_off << new_client->getRemoteAddress().toString() << " connected." << std::endl;
					std::cout << "There are now " << clients.size() << " client(s) connected." << std::endl;
					std::string server_info;
					server_info += std::to_string(clients.size() - 1) + " user(s) connected, excluding yourself.";

					send_packet("MOTD", motd, server_info, new_client);
				}
				else {
					std::cout << "A client tried to join but didn't quite manage." << std::endl;
					delete new_client;
				}
			}
			else {
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					if (selector.isReady(client)) {
						// this client sent data, so receive it
						sf::Packet packet;
						switch (client.receive(packet)) {
						case sf::Socket::Done: {
							std::string type;
							packet >> type;
							if (type == "MSG") {
								std::string name, body;
								packet >> name >> body;

								client2name[&client] = name;
								std::cout << bold_on << name << ": " << bold_off << body << std::endl;

								for (std::list<sf::TcpSocket*>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2) {
									sf::TcpSocket& client2send = **it2;
									client2send.send(packet);
								}
							}
							if (type == "NAME") {
								std::string name, body;
								packet >> name >> body;
								std::cout << client2name.at(&client) << " (" << client.getRemoteAddress() << ") changed their name to " << name << std::endl;
								client2name[&client] = name;
							}
							if (type == "check_queue") {
								string name;
								int player_amount;
								packet >> name >> player_amount;
								bool is_set = false;

								// being an exist queue game
								for (int i = 0; i < 10; i++) {
									if (!queue[i].empty && !queue[i].full && queue[i].player_amount == player_amount) {
										queue[i].p[queue[i].current_player_amount].player_name = name;
										queue[i].current_player_amount++;
										if (queue[i].current_player_amount == player_amount) queue[i].full = true;

										// set new client(player) the location code
										sf::Packet packet_location_code;
										packet_location_code << queue[i].p[queue[i].current_player_amount - 1].player_name << set_location_code << queue[i].current_player_amount - 1; // sent packet to told client their location code
										for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
											sf::TcpSocket& client = **it;
											client.send(packet_location_code);
										}

										// send MSG to remind someone being in room
										for (int j = 0; j < queue[i].player_amount; j++) {

											sf::Packet packet_MSG;

											packet_MSG << queue[i].p[j].player_name << enter_room << name;

											for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
												sf::TcpSocket& client = **it;
												client.send(packet_MSG);
											}

										}
										update_class(clients, queue[i], NAME);
										is_set = true;

										break;
									}

								}

								// join a new queue game
								if (!is_set) {
									for (int i = 0; i < 10; i++) {
										if (queue[i].empty) {
											queue[i].player_amount = player_amount;
											queue[i].p[0].player_name = name;
											queue[i].current_player_amount++;
											if (queue[i].current_player_amount == player_amount) queue[i].full = true;
											is_set = true;
											queue[i].empty = false;

											// send MSG to remind someone being in room
											for (int j = 0; j < queue[i].player_amount; j++) {

												sf::Packet packet_MSG;

												packet_MSG << queue[i].p[j].player_name << enter_room << name;

												for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
													sf::TcpSocket& client = **it;
													client.send(packet_MSG);
												}
											}

											sf::Packet packet_location_code;
											packet_location_code << queue[i].p[0].player_name << set_location_code << 0; // sent packet to told client their location code
											for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
												sf::TcpSocket& client = **it;
												client.send(packet_location_code);
											}
											break;
										}
									}
								}
							}
							if (type == "Draw_Over") {
								int location_code;
								packet >> location_code;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {
										for (int j = 0; j < 2; j++) {
											if (queue[i].current_pile.Pile_Card_Amount < 13)
												queue[i].current_pile.Shuffle_Card();
											queue[i].p[location_code].cards.Insert_Card(queue[i].current_pile.Pile_Card_Total->next->card_info.single_card_number, 1);
											queue[i].current_pile.Delete_Card(queue[i].current_pile.Pile_Card_Total->next->card_info.single_card_number);
										}
										update_class(clients, queue[i], Card_Sequence);
										// make play=card mode enable
										queue[i].turn_draw = -1;
										queue[i].turn_play = location_code;

										queue[i].p[location_code].gamestate = play_phase;
										update_class(clients, queue[i], Turn_State);

										// 										sf::Packet packet;
										// 										packet << queue[i].p[queue[i].current_turn].player_name << turn_play;
										// 										for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
										// 											sf::TcpSocket& client = **it;
										// 											client.send(packet);
									}
							}
							if (type == "Play_Over") {
								int location_code;
								packet >> location_code;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {

										// make play=card mode enable
										queue[i].turn_draw = -1;
										queue[i].turn_play = -1;
										queue[i].turn_discard = location_code;

										queue[i].p[location_code].gamestate = discard_phase;
										update_class(clients, queue[i], Turn_State);
									}
							}
							if (type == "Discard_Over") {
								int location_code;
								packet >> location_code;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {

										queue[i].p[location_code].gamestate = none;
										// make play=card mode enable
										queue[i].turn_draw = -1;
										queue[i].turn_play = -1;
										queue[i].turn_discard = -1;

										if (location_code == queue[i].player_amount - 1) location_code = 0;
										else location_code++;

										while (queue[i].p[location_code].gamestate == die) {
											if (location_code == queue[i].player_amount - 1) location_code = 0;
											else location_code++;
										}

										queue[i].turn_draw = location_code;
										queue[i].p[location_code].gamestate = draw_phase;

										update_class(clients, queue[i], Turn_State);
									}
							}
							if (type == "Animation") {
								int location_code;
								string animator;
								packet >> location_code >> animator;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {
										cout << "here there......" << endl;
										for (int j = 0; j < queue[i].player_amount; j++) {
											// send animator status to all client so to display it
											sf::Packet packet_animator;
											packet_animator << queue[i].p[j].player_name << update_info << location_code << Animation << animator; // sent packet to told client their location code
											for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
												sf::TcpSocket& client = **it;
												client.send(packet_animator);
											}
										}

									}

							}
							if (type == "Play_Card") {
								int location_code;
								string skill_type;
								packet >> location_code >> skill_type;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {
										if (skill_type == "kill" || skill_type == "analeptic_kill") {
											int victim_location_code;
											packet >> victim_location_code;

											// backup current turn state
											queue[i].turn_draw = -1;
											queue[i].turn_play = location_code;
											queue[i].turn_discard = -1;
											// change attacker's game-state & victim
											queue[i].p[location_code].gamestate = none;
											queue[i].p[victim_location_code].gamestate = defense_phase;

											update_class(clients, queue[i], Turn_State);

											queue[i].p[location_code].cards.Delete_Card(kill);

											update_class(clients, queue[i], Card_Sequence);

											// send signal that defender is enabled
											for (int j = 0; j < queue[i].player_amount; j++) {
												sf::Packet packet_defense;
												packet_defense << queue[i].p[j].player_name << update_info << victim_location_code << Defense_State << skill_type; // sent packet to told client their location code
												for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
													sf::TcpSocket& client = **it;
													client.send(packet_defense);
												}
											}

										}
										else if (skill_type == "peach") {
											if (queue[i].p[location_code].HP < queue[i].p[location_code].limited_HP) {
												queue[i].p[location_code].HP++;
												update_class(clients, queue[i], Hp);
											}
											queue[i].p[location_code].cards.Delete_Card(peach);
											update_class(clients, queue[i], Card_Sequence);
										}
										else if (skill_type == "analeptic") {
											queue[i].p[location_code].cards.Delete_Card(analeptic);
											update_class(clients, queue[i], Card_Sequence);
										}
										else if (skill_type == "amazing_grace") {
											queue[i].p[location_code].cards.Delete_Card(amazing_grace);
											for (int j = 0; j < queue[i].player_amount; j++) {

												if (queue[i].current_pile.Pile_Card_Amount < 13)
													queue[i].current_pile.Shuffle_Card();

												int num = queue[i].current_pile.Pile_Card_Total->next->card_info.single_card_number;
												queue[i].current_pile.Delete_Card(num);
												queue[i].p[j].cards.Insert_Card(num, 1);
											}
											update_class(clients, queue[i], Card_Sequence);
										}
									}

							}
							if (type == "Defense_Reply") {
								int location_code;
								string skill_type;
								packet >> location_code >> skill_type;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {
										if (skill_type == "jink") {
											// change attacker's game-state & victim
											queue[i].p[location_code].gamestate = none;
											queue[i].p[queue[i].turn_play].gamestate = play_phase;

											update_class(clients, queue[i], Turn_State);

											queue[i].p[location_code].cards.Delete_Card(jink);

											update_class(clients, queue[i], Card_Sequence);

										}
										else if (skill_type == "damage") {

											// change exturn turn to current turn
											queue[i].p[location_code].gamestate = none;
											queue[i].p[queue[i].turn_play].gamestate = play_phase;

											update_class(clients, queue[i], Turn_State);

											string kill_type;
											packet >> kill_type;
											if (kill_type == "single_kill") queue[i].p[location_code].HP--;
											else if (kill_type == "double_kill") queue[i].p[location_code].HP -= 2;

											update_class(clients, queue[i], Hp);

											if (queue[i].p[location_code].HP < 1) {

												queue[i].p[location_code].gamestate = dying_phase;
												queue[i].p[queue[i].turn_play].gamestate = defense_phase;
												queue[i].turn_dying = location_code;

												update_class(clients, queue[i], Turn_State);

												// send signal that peach begger is enabled
												for (int j = 0; j < queue[i].player_amount; j++) {
													sf::Packet packet_defense;
													packet_defense << queue[i].p[j].player_name << update_info << queue[i].turn_play << Defense_State << "begging_peach"; // sent packet to told client their location code
													for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
														sf::TcpSocket& client = **it;
														client.send(packet_defense);
													}
												}
											}


										}
										else if (skill_type == "give_peach") {

											queue[i].p[location_code].cards.Delete_Card(peach);
											update_class(clients, queue[i], Card_Sequence);

											queue[i].p[queue[i].turn_dying].HP++;
											update_class(clients, queue[i], Hp);

											if (queue[i].p[queue[i].turn_dying].HP > 0) {

												queue[i].p[queue[i].turn_play].gamestate = play_phase;
												queue[i].p[queue[i].turn_dying].gamestate = none;

												queue[i].turn_dying = -1;
												update_class(clients, queue[i], Turn_State);
											}
											else {
												for (int j = 0; j < queue[i].player_amount; j++) {
													sf::Packet packet_defense;
													packet_defense << queue[i].p[j].player_name << update_info << location_code << Defense_State << "begging_peach"; // sent packet to told client their location code
													for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
														sf::TcpSocket& client = **it;
														client.send(packet_defense);
													}
												}
											}
										}
										else if (skill_type == "reject_peach") {

											queue[i].p[location_code].gamestate = none;

											int next_turn;
											if (location_code == queue[i].player_amount - 1) next_turn = 0;
											else next_turn = location_code + 1;

											while (queue[i].p[next_turn].gamestate == die) {
												if (next_turn == queue[i].player_amount - 1) next_turn = 0;
												else next_turn = next_turn + 1;
											}

											if (next_turn == queue[i].turn_dying) {  // for self-saving
												queue[i].p[queue[i].turn_dying].gamestate == defense_phase;
												queue[i].p[queue[i].turn_play].gamestate = none;

												// send signal that defender is enabled
												for (int j = 0; j < queue[i].player_amount; j++) {
													sf::Packet packet_defense;
													packet_defense << queue[i].p[j].player_name << update_info << next_turn << Defense_State << "self_save"; // sent packet to told client their location code
													for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
														sf::TcpSocket& client = **it;
														client.send(packet_defense);
													}
												}
											}
											else if (next_turn == queue[i].turn_play) {

												queue[i].p[queue[i].turn_dying].gamestate = die;
												queue[i].p[queue[i].turn_play].gamestate = play_phase;

												queue[i].turn_dying = -1;

											}
											else {

												queue[i].p[location_code].gamestate = none;
												queue[i].p[next_turn].gamestate = defense_phase;

												for (int j = 0; j < queue[i].player_amount; j++) {
													sf::Packet packet_defense;
													packet_defense << queue[i].p[j].player_name << update_info << next_turn << Defense_State << "begging_peach"; // sent packet to told client their location code
													for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
														sf::TcpSocket& client = **it;
														client.send(packet_defense);
													}
												}
											}
											update_class(clients, queue[i], Turn_State);
										}
										else if (skill_type == "selfsave") {
											int card_type;
											packet >> card_type;
											queue[i].p[location_code].cards.Delete_Card(card_type);
											update_class(clients, queue[i], Card_Sequence);

											queue[i].p[location_code].HP++;
											if (queue[i].p[location_code].HP > 0) {
												queue[i].p[queue[i].turn_play].gamestate = play_phase;
												queue[i].p[location_code].gamestate = none;
												update_class(clients, queue[i], Turn_State);
											}
											else {
												// send signal that defender is enabled
												for (int j = 0; j < queue[i].player_amount; j++) {
													sf::Packet packet_defense;
													packet_defense << queue[i].p[j].player_name << update_info << location_code << Defense_State << "self_save"; // sent packet to told client their location code
													for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
														sf::TcpSocket& client = **it;
														client.send(packet_defense);
													}
												}
											}
											update_class(clients, queue[i], Hp);
										}
										else if (skill_type == "reject_selfsave") {

											queue[i].p[location_code].gamestate = dying_phase;

											int next_turn;
											if (location_code == queue[i].player_amount - 1) next_turn = 0;
											else next_turn = location_code + 1;

											while (queue[i].p[next_turn].gamestate == die) {
												if (next_turn == queue[i].player_amount - 1) next_turn = 0;
												else next_turn = next_turn + 1;
											}

											if (next_turn == queue[i].turn_play) {

												queue[i].p[queue[i].turn_dying].gamestate = die;
												queue[i].p[queue[i].turn_play].gamestate = play_phase;

												queue[i].turn_dying = -1;
											}
											else {

												queue[i].p[next_turn].gamestate = defense_phase;

												for (int j = 0; j < queue[i].player_amount; j++) {
													sf::Packet packet_defense;
													packet_defense << queue[i].p[j].player_name << update_info << next_turn << Defense_State << "begging_peach"; // sent packet to told client their location code
													for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
														sf::TcpSocket& client = **it;
														client.send(packet_defense);
													}
												}
											}
											update_class(clients, queue[i], Turn_State);

										}
									}
							}
							if (type == "Discard_Card") {
								int location_code;
								int card_type;
								packet >> location_code >> card_type;
								for (int i = 0; i < 10; i++)
									if (queue[i].game_start) {
										if (card_type == (-2)) {
											update_class(clients, queue[i], Card_Sequence);
										}
										else {
											queue[i].p[location_code].cards.Delete_Card(card_type);
										}
									}
							}
						}break;
						case sf::Socket::Disconnected: {
							std::string displayname;
							displayname = client2name.at(&client);

							std::cout << bold_on << "** " << bold_off <<
								displayname << " disconnected." << std::endl;
							selector.remove(client);
							client.disconnect();
							delete(&client);
							clients.erase(it);
							client2name.erase(&client);
							it--;

							for (std::list<sf::TcpSocket*>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2) {
								sf::TcpSocket& client2send = **it2;
								send_packet("DISCON", displayname, "Disconnected.", &client2send);
							}
						}break;
						default:
							break;
						}
					}
				}
			}
		}

		/*-----------------for initial --------------------------*/
		for (int i = 0; i < 10; i++)
			if (queue[i].full && !queue[i].game_start) {

				queue[i].current_pile.Shuffle_Card();

				for (int j = 0; j < queue[i].player_amount; j++) {
					// initialize game state
					queue[i].p[j].gamestate = none;
					// send the MSG of game start so to print in client MSG boxes
					sf::Packet packet;
					packet << queue[i].p[j].player_name << game_start;
					for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
						sf::TcpSocket& client = **it;
						client.send(packet);
					}
					// initialize add card to each queue -->p --- 4 cards
					for (int no = 0; no < 4; no++) {
						int num = queue[i].current_pile.Pile_Card_Total->next->card_info.single_card_number;
						queue[i].p[j].cards.Insert_Card(num, 1);
						queue[i].current_pile.Delete_Card(num);
					}
				}

				update_class(clients, queue[i], Hp);
				update_class(clients, queue[i], Limit_Hp);
				update_class(clients, queue[i], Card_Sequence);

				queue[i].current_turn = 0;
				// a chance to start up
				queue[i].turn_draw = 0;
				queue[i].p[0].gamestate = draw_phase;
				update_class(clients, queue[i], Turn_State);
				// 					sf::Packet packet;
				// 					packet << queue[i].p[queue[i].current_turn].player_name << turn_draw;
				// 					for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
				// 						sf::TcpSocket& client = **it;
				// 						client.send(packet);
				// 					}
				queue[i].game_start = true;
			}
		/*-----------------end initial --------------------------*/


	}

}


