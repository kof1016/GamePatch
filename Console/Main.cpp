// Main.cpp : Defines the entry point for the console application.
//

#include "FirstState.h"
#include "SecondState.h"
#include <iostream>
#include <conio.h> 
#include "../Utility/StateMachine.h"
#include "curl/curl.h"

Utility::StateMachine StateMachine;

void _ToSecondState()
{
	const auto state = new State::SecondState();
	//state->OnDone = &_ToSecondState;

	StateMachine.Push(state);
}

void _ToFirstState()
{
	const auto state = new State::FirstState();
	state->OnDone = &_ToSecondState;

	StateMachine.Push(state);
}

int main(int argc, char* argv[])
{
	// _ToFirstState();
 //
	// int n = _kbhit();
	// while(true)
	// {
	// 	if(_kbhit()!=0)
	// 	{
	// 		if(_getch() == 0x32)
	// 		{
	// 			StateMachine.Termination();
	// 			break;
	// 		}
	// 	}
 //
	// 	StateMachine.Update();
	// }

	//  CURL *curl = nullptr;
	//  CURLcode res;
	//  curl = curl_easy_init();
	// if (curl != nullptr)
	// {
	// 	//curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
	// 	curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se/libcurl/c/htmltitle.html");
	// 	/* example.com is redirected, so we tell libcurl to follow redirection */
	// 	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	// 	/* Perform the request, res will get the return code */
	// 	res = curl_easy_perform(curl);
	// 	/* Check for errors */
	// 	if (res != CURLE_OK) {
	// 		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	// 	}
	// 	/* always cleanup */
	// 	curl_easy_cleanup(curl);
	// }
	
	return 0;
}
