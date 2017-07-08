void move_enemy()
{
    if(vidaIni1==1){
        if(In1_position.x!=player_position.x && In1_position.y!=player_position.y)
        {
            
            if(In1_position.x>player_position.x)
            {
                if(In1_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x -= j;
                        In1_position.y -=j;
                        In1_frame.x=50;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In1_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x -= j;
                        In1_position.y +=j;
                        In1_frame.x=150;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In1_position.x<player_position.x)
            {
                if(In1_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x += j;
                        In1_position.y -=j;
                        In1_frame.x=350;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In1_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x += j;
                        In1_position.y +=j;
                        In1_frame.x=250;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In1_position.x!=player_position.x && In1_position.y==player_position.y)
        {
            
            if(In1_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x -= j;
                        In1_frame.x=100;
                        if(In1_position.x==player_position.x)
                            j=2;
                    } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x += j;
                        In1_frame.x=300;
                        if(In1_position.x==player_position.x)
                            j=2;
                    } 
            }
        }
        else if(In1_position.x==player_position.x && In1_position.y!=player_position.y)
        {
            
            if(In1_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.y -= j;
                        In1_frame.x=0;
                        if(In1_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.y += j;
                        In1_frame.x=200;
                        if(In1_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In1_position.x==player_position.x && In1_position.y==player_position.y)
        {
            vidaIni1=0;
            vida--;
        }

    }
    if(vidaIni2==1)
    {
        if(In2_position.x!=player_position.x && In2_position.y!=player_position.y)
        {
            
            if(In2_position.x>player_position.x)
            {
                if(In2_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x -= j;
                        In2_position.y -=j;
                        In2_frame.x=53;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In2_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x -= j;
                        In2_position.y +=j;
                        In2_frame.x=159;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In2_position.x<player_position.x)
            {
                if(In2_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x += j;
                        In2_position.y -=j;
                        In2_frame.x=371;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In2_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x += j;
                        In2_position.y +=j;
                        In2_frame.x=265;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In2_position.x!=player_position.x && In2_position.y==player_position.y)
        {
            
            if(In2_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x -= j;
                        In2_frame.x=106;
                        if(In2_position.x==player_position.x)
                            j=2;
                    } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x += j;
                        In2_frame.x=318;
                        if(In2_position.x==player_position.x)
                            j=2;
                    } 
            }
        }
        else if(In2_position.x==player_position.x && In2_position.y!=player_position.y)
        {
            
            if(In2_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.y -= j;
                        In2_frame.x=0;
                        if(In2_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.y += j;
                        In2_frame.x=212;
                        if(In2_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In2_position.x==player_position.x && In2_position.y==player_position.y)
        {
            vidaIni2=0;
            vida--;
        }

    }
    if(vidaIni3==1)
    {
        if(In3_position.x!=player_position.x && In3_position.y!=player_position.y)
        {
            if(In3_position.x>player_position.x)
            {
                if(In3_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x -= j;
                        In3_position.y -=j;
                        In3_frame.x=53;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In3_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x -= j;
                        In3_position.y +=j;
                        In3_frame.x=159;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In3_position.x<player_position.x)
            {
                if(In3_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x += j;
                        In3_position.y -=j;
                        In3_frame.x=371;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In3_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x += j;
                        In3_position.y +=j;
                        In3_frame.x=265;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In3_position.x!=player_position.x && In3_position.y==player_position.y)
        {
            
            if(In3_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In3_position.x -= j;
                    In3_frame.x=106;
                    if(In3_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In3_position.x += j;
                    In3_frame.x=318;
                    if(In3_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In3_position.x==player_position.x && In3_position.y!=player_position.y)
        {
            
            if(In3_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.y -= j;
                        In3_frame.x=0;
                        if(In3_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.y += j;
                        In3_frame.x=212;
                        if(In3_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In3_position.x==player_position.x && In3_position.y==player_position.y)
        {
            vidaIni3=0;
            vida--;
        }
    }
    if(vidaIni4==1)
    {
        if(In4_position.x!=player_position.x && In4_position.y!=player_position.y)
        {
            if(In4_position.x>player_position.x)
            {
                if(In4_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x -= j;
                        In4_position.y -=j;
                        In4_frame.x=53;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In4_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x -= j;
                        In4_position.y +=j;
                        In4_frame.x=159;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In4_position.x<player_position.x)
            {
                if(In4_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x += j;
                        In4_position.y -=j;
                        In4_frame.x=371;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In4_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x += j;
                        In4_position.y +=j;
                        In4_frame.x=265;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In4_position.x!=player_position.x && In4_position.y==player_position.y)
        {
            
            if(In4_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In4_position.x -= j;
                    In4_frame.x=106;
                    if(In4_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In4_position.x += j;
                    In4_frame.x=318;
                    if(In4_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In4_position.x==player_position.x && In4_position.y!=player_position.y)
        {
            
            if(In4_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.y -= j;
                        In4_frame.x=0;
                        if(In4_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.y += j;
                        In4_frame.x=212;
                        if(In4_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In4_position.x==player_position.x && In4_position.y==player_position.y)
        {
            vidaIni4=0;
            vida--;
        }
    }
        if(vidaIni5==1){
        if(In5_position.x!=player_position.x && In5_position.y!=player_position.y)
        {
            
            if(In5_position.x>player_position.x)
            {
                if(In5_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x -= j;
                        In5_position.y -=j;
                        In5_frame.x=50;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In5_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x -= j;
                        In5_position.y +=j;
                        In5_frame.x=150;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In5_position.x<player_position.x)
            {
                if(In5_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x += j;
                        In5_position.y -=j;
                        In5_frame.x=350;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In5_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x += j;
                        In5_position.y +=j;
                        In5_frame.x=250;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In5_position.x!=player_position.x && In5_position.y==player_position.y)
        {
            
            if(In5_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x -= j;
                        In5_frame.x=100;
                        if(In5_position.x==player_position.x)
                            j=2;
                    } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x += j;
                        In5_frame.x=300;
                        if(In5_position.x==player_position.x)
                            j=2;
                    } 
            }
        }
        else if(In5_position.x==player_position.x && In5_position.y!=player_position.y)
        {
            
            if(In5_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.y -= j;
                        In5_frame.x=0;
                        if(In5_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.y += j;
                        In5_frame.x=200;
                        if(In5_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In5_position.x==player_position.x && In5_position.y==player_position.y)
        {
            vidaIni5=0;
            vida--;
        }

    }
    if(vidaIni6==1)
    {
        if(In6_position.x!=player_position.x && In6_position.y!=player_position.y)
        {
            if(In6_position.x>player_position.x)
            {
                if(In6_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x -= j;
                        In6_position.y -=j;
                        In6_frame.x=53;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In6_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x -= j;
                        In6_position.y +=j;
                        In6_frame.x=159;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In6_position.x<player_position.x)
            {
                if(In6_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x += j;
                        In6_position.y -=j;
                        In6_frame.x=371;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In4_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x += j;
                        In6_position.y +=j;
                        In6_frame.x=265;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In6_position.x!=player_position.x && In6_position.y==player_position.y)
        {
            
            if(In6_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In6_position.x -= j;
                    In6_frame.x=106;
                    if(In6_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In6_position.x += j;
                    In6_frame.x=318;
                    if(In6_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In6_position.x==player_position.x && In6_position.y!=player_position.y)
        {
            
            if(In6_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.y -= j;
                        In6_frame.x=0;
                        if(In6_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.y += j;
                        In6_frame.x=212;
                        if(In6_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In6_position.x==player_position.x && In6_position.y==player_position.y)
        {
            vidaIni6=0;
            vida--;
        }

    }
    if(vidaIni7==1)
    {
        if(In7_position.x!=player_position.x && In7_position.y!=player_position.y)
        {
            if(In7_position.x>player_position.x)
            {
                if(In7_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x -= j;
                        In7_position.y -=j;
                        In7_frame.x=53;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In7_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x -= j;
                        In7_position.y +=j;
                        In7_frame.x=159;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In7_position.x<player_position.x)
            {
                if(In7_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x += j;
                        In7_position.y -=j;
                        In7_frame.x=371;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In7_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x += j;
                        In7_position.y +=j;
                        In7_frame.x=265;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In7_position.x!=player_position.x && In7_position.y==player_position.y)
        {
            
            if(In7_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In7_position.x -= j;
                    In7_frame.x=106;
                    if(In7_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In7_position.x += j;
                    In7_frame.x=318;
                    if(In7_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In7_position.x==player_position.x && In7_position.y!=player_position.y)
        {
            
            if(In7_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.y -= j;
                        In7_frame.x=0;
                        if(In7_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.y += j;
                        In7_frame.x=212;
                        if(In7_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In7_position.x==player_position.x && In7_position.y==player_position.y)
        {
            vidaIni7=0;
            vida--;
        }

    }
    if(vidaIni8==1)
    {
        if(In8_position.x!=player_position.x && In8_position.y!=player_position.y)
        {
            if(In8_position.x>player_position.x)
            {
                if(In8_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x -= j;
                        In8_position.y -=j;
                        In8_frame.x=53;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In8_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x -= j;
                        In8_position.y +=j;
                        In8_frame.x=159;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In8_position.x<player_position.x)
            {
                if(In8_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x += j;
                        In8_position.y -=j;
                        In8_frame.x=371;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In8_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x += j;
                        In8_position.y +=j;
                        In8_frame.x=265;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In8_position.x!=player_position.x && In8_position.y==player_position.y)
        {
            
            if(In8_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In8_position.x -= j;
                    In8_frame.x=106;
                    if(In8_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In8_position.x += j;
                    In8_frame.x=318;
                    if(In8_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In8_position.x==player_position.x && In8_position.y!=player_position.y)
        {
            
            if(In8_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.y -= j;
                        In8_frame.x=0;
                        if(In8_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.y += j;
                        In8_frame.x=212;
                        if(In8_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In8_position.x==player_position.x && In8_position.y==player_position.y)
        {
            vidaIni8=0;
            vida--;
        }

    }
}
