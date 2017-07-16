void apareceVagabundo1()
{

    //Rect do frame
    In5_frame.x = 0;
    In5_frame.y = 0;
    In5_frame.w = in_frameW;
    In5_frame.h = in_frameH;
    //Rect da posição do player na tela
    In5_position.x = (SCREEN_WIDTH/2);
    In5_position.y = 0;
    In5_position.w = 53;
    In5_position.h = in_frameH;
    //Rect do frame
    In6_frame.x = 0;
    In6_frame.y = 0;
    In6_frame.w = 53;
    In6_frame.h = in_frameH;
    //Rect da posição do player na tela
    In6_position.x = 0;
    In6_position.y = (SCREEN_HEIGHT/2);
    In6_position.w = in_frameW;
    In6_position.h = in_frameH;
    //Rect do frame
    In7_frame.x = 0;
    In7_frame.y = 0;
    In7_frame.w = 53;
    In7_frame.h = in_frameH;
    //Rect da posição do player na tela
    In7_position.x = SCREEN_WIDTH/2;
    In7_position.y = SCREEN_HEIGHT-63;
    In7_position.w = in_frameW;
    In7_position.h = in_frameH;
    //Rect do frame
    In8_frame.x = 0;
    In8_frame.y = 0;
    In8_frame.w = in_frameW;
    In8_frame.h = in_frameH;
    //Rect da posição do player na tela
    In8_position.x = SCREEN_WIDTH-63;
    In8_position.y = SCREEN_HEIGHT/2;
    In8_position.w = 53;
    In8_position.h = in_frameH;

    vidaIni5=1;//inimigo 5
    vidaIni6=1;//inimigo 6
    vidaIni7=1;//inimigo 7
    vidaIni8=1;//inimigo 8

    //totInimigos=vidaIni4+vidaIni3+vidaIni2+vidaIni1;
}

void apareceVagabundo()
{

    //Rect do frame
    In1_frame.x = 0;
    In1_frame.y = 0;
    In1_frame.w = in_frameW;
    In1_frame.h = in_frameH;
    //Rect da posição do player na tela
    In1_position.x = 0;
    In1_position.y = 0;
    In1_position.w = in_frameW;
    In1_position.h = in_frameH;
    //Rect do frame
    In2_frame.x = 0;
    In2_frame.y = 0;
    In2_frame.w = 53;
    In2_frame.h = in_frameH;
    //Rect da posição do player na tela
    In2_position.x = 0;
    In2_position.y = SCREEN_HEIGHT-63;
    In2_position.w = in_frameW;
    In2_position.h = in_frameH;
    //Rect do frame
    In3_frame.x = 0;
    In3_frame.y = 0;
    In3_frame.w = 53;
    In3_frame.h = in_frameH;
    //Rect da posição do player na tela
    In3_position.x = 837;
    In3_position.y = 0;
    In3_position.w = in_frameW;
    In3_position.h = in_frameH;
    //Rect do frame
    In4_frame.x = 0;
    In4_frame.y = 0;
    In4_frame.w = in_frameW;
    In4_frame.h = in_frameH;
    //Rect da posição do player na tela
    In4_position.x = SCREEN_WIDTH-63;
    In4_position.y = SCREEN_HEIGHT-63;
    In4_position.w = 53;
    In4_position.h = in_frameH;

    vidaIni1=1;//inimigos 1
    vidaIni2=1;//inimigo 2
    vidaIni3=1;//inimigo 3
    vidaIni4=1;//inimigo 4

    //totInimigos=vidaIni4+vidaIni3+vidaIni2+vidaIni1;
}