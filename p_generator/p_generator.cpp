// p_generator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define IDLE_MODE__SLEEP_TIME_MSECS		0

// key codes - defined in <winuser.h>
#define VK_ESCAPE		0x1B
#define VK_RETURN		0x0D
#define VK_SPACE		0x20

#define SRAND_INIT()		srand( static_cast<unsigned>( time(nullptr) ) ); rand()
#define LOOP_INFINITE		while (true)

#define NEWLINE_DEFINE(v)	bool is_newline = ##v
#define NEWLINE_PRINT()		if ( is_newline ) { is_newline = !is_newline; wprintf_s( L"\n" ); }
#define NEWLINE_UPDATE(v)	is_newline = ##v

void echo_keys(
) {
	typedef std::pair< cstr_t, cstr_t > key_info;
	const key_info keys_info[] =
	{
		{ L"space", L"new dice (random generator value)" },
		{ L"enter", L"new random generator re-initialization" },
		{ L"esc", L"exit from utility" }
	};

	wprintf_s( L"awailable keys:\n" );
	for ( const auto &key_info: keys_info )
		wprintf_s( L"  [%s] - %s\n", key_info.first, key_info.second );
	wprintf_s( L"\n" );
}


int wmain(
	_in unsigned argc, 
	_in cstr_t argv[]
) {
	echo_keys();

	NEWLINE_DEFINE( false );
	SRAND_INIT();

	LOOP_INFINITE 
	{
		if ( !_kbhit() )
		{
			_sleep( IDLE_MODE__SLEEP_TIME_MSECS );
			continue;
		}

		switch ( _getch() )
		{
			case VK_RETURN:
				NEWLINE_PRINT();
				wprintf_s( L"random generator re-initialization..." );
				SRAND_INIT();
				wprintf_s( L" ok\n" );
				break;

			case VK_SPACE:
				NEWLINE_UPDATE( true );
				{
					const auto rand_v = rand();
					wprintf_s( rand_v < ((RAND_MAX+1) >> 1) ? L"-" : L"+" );
				}
				break;

			case VK_ESCAPE:
				NEWLINE_PRINT();
				wprintf_s( L"exiting..." );
				goto exit;
		}
	}

exit:
	wprintf_s( L" ok\n" );
	return 0;
}