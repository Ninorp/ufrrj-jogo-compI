void Menu()
{
    cursor_position.y=278;
    while(option!=1)         //Menu
    {
        Mix_PlayMusic( music, -1 );
        while(opcao==0)    
        {
            SDL_BlitSurface(menu, NULL, Screen, NULL);
            SDL_BlitSurface(cursor, NULL, Screen, &cursor_position);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_1:
                            option = 1;
                        break;
                        case SDLK_2:
                            option = 2;
                        break;
                        case SDLK_3:
                            option = 3;
                        break;
                        case SDLK_4:
                            option = 4;
                        break;
                        case SDLK_5:
                            option = 5;
                        break;
                        case SDLK_DOWN:
                            if(cursor_position.y!=434)
                                cursor_position.y+=39;
                            else
                                cursor_position.y=278;
                        break;
                        case SDLK_UP:
                            if(cursor_position.y!=278)
                                cursor_position.y-=39;
                            else
                                cursor_position.y=434;
                        break;
                        case SDLK_RETURN:
                            if(cursor_position.y==278)
                                option = 1;
                            else if(cursor_position.y==317)
                                option = 2;
                            else if(cursor_position.y==356)
                                option = 3;
                            else if(cursor_position.y==395)
                                option = 4;
                            else
                                option = 5;
                        break;
                    }
                }
            }
        }
        
        while(option == 3)     //Records
        {
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            read_record();
            show_record();
            //SDL_BlitSurface(records, NULL, janela_menu, NULL);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            option = 0;
                        break;
                    }
                }
            }
        }
        while(option == 2)      //Instrucoes
        {
            SDL_BlitSurface(instrucoes, NULL, Screen, NULL);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            option = 0;
                        break;
                    }
                }
            }
        }
        while(option == 4)     //Sobre
        {
            SDL_BlitSurface(creditos, NULL, Screen, NULL);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            option = 0;
                        break;
                    }
                }
            }
        }
        while(option == 5)  //Sair
        {
            //Liberar as imagens da memória
            SDL_FreeSurface(Background);
            SDL_FreeSurface(Player);
            SDL_FreeSurface(In1);
            SDL_FreeSurface(In2);
            SDL_FreeSurface(In3);
            SDL_FreeSurface(lose);
            SDL_FreeSurface(menu);
            SDL_FreeSurface(bullet);
            SDL_FreeSurface(creditos);
            SDL_FreeSurface(instrucoes);
            SDL_FreeSurface(Boss);
            SDL_FreeSurface(escrever);
            SDL_FreeSurface(Bos);
            SDL_FreeSurface(bullet2);
            SDL_FreeSurface(bullet3);
            SDL_FreeSurface(in4);
            //Destruir janela
            SDL_DestroyWindow( window );
            //Encerra o SDL
            SDL_Quit();
            exit(1);
        }
    }
  

    if(option == 1)      //Condicao do menu relativa a jogar
    {
        /*apareceVagabundo();
        apareceVagabundo1();*/
        gameRunning=1;
        vida=5;
        player_frame.x = 0;
        player_frame.y = 0;
        player_position.x = (SCREEN_WIDTH/2);
        player_position.y = (SCREEN_HEIGHT/2);
        pont=0;
        SDL_Delay(500);//delay do menu para o jogo
        fase1();
    }
}