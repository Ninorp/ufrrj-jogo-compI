//Antes do Main
//recorde
int rec[5];
char recordes1[100];
char recordes2[100];
char recordes3[100];
char recordes4[100];
char recordes5[100];
SDL_Surface* Recordes[10];


void read_record()
{
    pe=fopen("rec.txt" , "r");
    for(e=0; e<5; e++)
    {
        fscanf(pe, "%d", &rec[e]);
        if(e==0)
        {
            sprintf(recordes1, "1:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes1, cor);
        }
        else if(e==1)
        {
            sprintf(recordes2, "2:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes2, cor);
        }
        else if(e==2)
        {
            sprintf(recordes3, "3:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes3, cor);
        }
        else if(e==3)
        {
            sprintf(recordes4, "4:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes4, cor);
        }
        else if(e==4)
        {
            sprintf(recordes5, "5:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes5, cor);
        }
    }
    fclose(pe);
}
void show_record()
{
    for(e=0; e<5; e++)
    {
        if(e==0)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec1);
        else if(e==1)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec2);
        else if(e==2)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec3);
        else if(e==3)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec4);
        else if(e==4)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec5);
    }
}

void save_record()
{
    ps=fopen("rec.txt" , "w");
    for(e=0; e<5; e++)
    {
        if(pont>rec[e])
        {
            aux=rec[e];
            rec[e]=pont;
            pont=aux;
        }
    }
    for(e=0; e<5; e++)
    {
        fprintf(ps, "%d\n", rec[e]);
    }
    fclose(ps);