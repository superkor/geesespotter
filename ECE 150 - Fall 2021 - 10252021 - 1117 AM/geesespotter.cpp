#include "geesespotter_lib.h"
#include <iostream>
//#include <cmath>

int main();
char *createBoard(std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);
void spreadGeese(char *board, std::size_t xdim, std::size_t ydim, unsigned int numGeese);

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    for (int counter{0}; counter < ydim*xdim; counter++){
        //(0,0) corner
        if (counter == 0 && xloc == 0 && yloc == 0){
            //check if field is already revealed
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } //reveal all surrounding fields
            else{
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter+1]-0x20 < 0x09 && board[counter+1]>=0x20){
                        board[counter+1] -= 0x20;
                    } 
                    if (board[counter+xdim]-0x20 < 0x09 && board[counter+xdim]>=0x20){
                        board[counter+xdim] -= 0x20;
                    } 
                    if (board[counter+xdim+1]-0x20 < 0x09 && board[counter+xdim+1]>=0x20){
                        board[counter+xdim+1] -= 0x20;
                    } 
                }
                return 0;
            }
        } // top right corner
        else if (counter == xdim-1 && xloc == xdim-1 && yloc == 0){
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                    if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter-1]-0x20 < 0x09 && board[counter-1]>=0x20){
                        board[counter-1] -= 0x20;
                    } 
                    if (board[counter+xdim]-0x20 < 0x09 && board[counter+xdim]>=0x20){
                        board[counter+xdim] -= 0x20;
                    } 
                    if (board[counter+xdim-1]-0x20 < 0x09 && board[counter+xdim-1]>=0x20){
                        board[counter+xdim-1] -= 0x20;
                    } 
                }
                return 0;
            }
        } // top row 
        else if (counter == xloc && xloc < xdim && yloc == 0 && counter !=0){
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter-1]-0x20 < 0x09 && board[counter-1]>=0x20){
                        board[counter-1] -= 0x20;
                    } 
                    if (board[counter+1]-0x20 < 0x09 && board[counter+1]>=0x20){
                        board[counter+1] -= 0x20;
                    }
                    if (board[counter+xdim]-0x20 < 0x09 && board[counter+xdim]>=0x20){
                        board[counter+xdim] -= 0x20;
                    } 
                    if (board[counter+xdim-1]-0x20 < 0x09 && board[counter+xdim-1]>=0x20){
                        board[counter+xdim-1] -= 0x20;
                    } 
                    if (board[counter+xdim+1]-0x20 < 0x09 && board[counter+xdim+1]>=0x20){
                        board[counter+xdim+1] -= 0x20;
                    }
                }
                return 0;
            }
        } // bottom left corner
        else if (counter == xdim*(ydim-1) && xloc == 0 && yloc == ydim-1){
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } ///check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter+1]-0x20 < 0x09 && board[counter+1]>=0x20){
                        board[counter+1] -= 0x20;
                    } 
                    if (board[counter-xdim]-0x20 < 0x09 && board[counter-xdim]>=0x20){
                        board[counter-xdim] -= 0x20;
                    } 
                    if (board[counter-xdim+1]-0x20 < 0x09 && board[counter-xdim+1]>=0x20){
                        board[counter-xdim+1] -= 0x20;
                    } 
                }
                return 0;
            }
        } // bottom right corner
        else if (counter == (xdim*ydim)-1 && xloc == xdim-1 && yloc == ydim-1){
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter-1]-0x20 < 0x09 && board[counter-1]>=0x20){
                        board[counter-1] -= 0x20;
                    } 
                    if (board[counter-xdim]-0x20 < 0x09 && board[counter-xdim]>=0x20){
                        board[counter-xdim] -= 0x20;
                    } 
                    if (board[counter-xdim-1]-0x20 < 0x09 && board[counter-xdim-1]>=0x20){
                        board[counter-xdim-1] -= 0x20;
                    } 
                }
                return 0;
            }
        } //bottom row
        else if (counter == xdim*(yloc)+xloc && yloc == ydim-1 && xloc != xdim-1 && xloc != 0){
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter-1]-0x20 < 0x09 && board[counter-1]>=0x20){
                        board[counter-1] -= 0x20;
                    } 
                    if (board[counter+1]-0x20 < 0x09 && board[counter+1]>=0x20){
                        board[counter+1] -= 0x20;
                    }
                    if (board[counter-xdim]-0x20 < 0x09 && board[counter-xdim]>=0x20){
                        board[counter-xdim] -= 0x20;
                    } 
                    if (board[counter-xdim-1]-0x20 < 0x09 && board[counter-xdim-1]>=0x20){
                        board[counter-xdim-1] -= 0x20;
                    }
                    if (board[counter-xdim+1]-0x20 < 0x09 && board[counter-xdim+1]>=0x20){
                        board[counter-xdim+1] -= 0x20;
                    }
                    
                }
                return 0;
            }
        } //left most column
        else if (counter==xdim*(yloc) && xloc == 0 && yloc !=0 && yloc!=ydim-1 && counter>xdim){
             if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter+1]-0x20 < 0x09 && board[counter+1]>=0x20){
                        board[counter+1] -= 0x20;
                    } 
                    if (board[counter-xdim]-0x20 < 0x09 && board[counter-xdim]>=0x20){
                        board[counter-xdim] -= 0x20;
                    } 
                    if (board[counter+xdim]-0x20 < 0x09 && board[counter+xdim]>=0x20){
                        board[counter+xdim] -= 0x20;
                    }
                    if (board[counter-xdim+1]-0x20 < 0x09 && board[counter-xdim+1]>=0x20){
                        board[counter-xdim+1] -= 0x20;
                    }
                    if (board[counter+xdim+1]-0x20 < 0x09 && board[counter+xdim+1]>=0x20){
                        board[counter+xdim+1] -= 0x20;
                    }

                }
                return 0;
            }
        }//right most column
        else if (counter==xdim*(yloc)+xloc && xloc == xdim-1 && yloc !=0 && yloc != ydim-1){
            std::cout << counter << std::endl;
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter-1]-0x20 < 0x09 && board[counter-1]>=0x20){
                        board[counter-1] -= 0x20;
                    } 
                    if (board[counter-xdim]-0x20 < 0x09 && board[counter-xdim]>=0x20){
                        board[counter-xdim] -= 0x20;
                    } 
                    if (board[counter+xdim]-0x20 < 0x09 && board[counter+xdim]>=0x20){
                        board[counter+xdim] -= 0x20;
                    }
                    if (board[counter-xdim-1]-0x20 < 0x09 && board[counter-xdim-1]>=0x20){
                        board[counter-xdim-1] -= 0x20;
                    }
                    if (board[counter+xdim-1]-0x20 < 0x09 && board[counter+xdim-1]>=0x20){
                        board[counter+xdim-1] -= 0x20;
                    }
                    
                }
                return 0;
            }
        }// everything else
        else if (counter == xloc+yloc*xdim){
            if (board[counter] < 0x20){
                return 2;
            }//check if field is marked 
            else if (board[counter] >= 0x30){
                return 1;
            } //check if field has a goose. reveal field even if mr goose is there
            else if (board[counter]==0x29){
                board[counter] -= 0x20;
                return 9;
            } else {
                board[counter] -= 0x20;
                if (board[counter]==0x0){
                    //check if surrounding fields have goose. if not, also reveal
                    if (board[counter-1]-0x20 < 0x09 && board[counter-1]>=0x20){
                        board[counter-1] -= 0x20;
                    } 
                    if (board[counter+1]-0x20 < 0x09 && board[counter+1]>=0x20){
                        board[counter+1] -= 0x20;
                    }
                    if (board[counter-xdim]-0x20 < 0x09 && board[counter-xdim]>=0x20){
                        board[counter-xdim] -= 0x20;
                    } 
                    if (board[counter+xdim]-0x20 < 0x09 && board[counter+xdim]>=0x20){
                        board[counter+xdim] -= 0x20;
                    }
                    if (board[counter-xdim-1]-0x20 < 0x09 && board[counter-xdim-1]>=0x20){
                        board[counter-xdim-1] -= 0x20;
                    }
                    if (board[counter+xdim-1]-0x20 < 0x09 && board[counter+xdim-1]>=0x20){
                        board[counter+xdim-1] -= 0x20;
                    }
                    if (board[counter-xdim+1]-0x20 < 0x09 && board[counter-xdim+1]>=0x20){
                        board[counter-xdim+1] -= 0x20;
                    }
                    if (board[counter+xdim+1]-0x20 < 0x09 && board[counter+xdim+1]>=0x20){
                        board[counter+xdim+1] -= 0x20;
                    }
                }
                return 0;
            }
        }
    }
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){
    int numGeese{}, checkGeese{};

    for (int check{0}; check < xdim*ydim; check++){
        if (board[check] >= 0x30){
            if(board[check]-=0x30 == 0x09){
                checkGeese++;
            }
        } else if (board[check] >= 0x20){
            if (board[check] -=0x20 == 0x09){
                checkGeese++;
            }
        }
    }

    for (int counter{0}; counter < xdim*ydim; counter++){
        //check if field is marked
        if (board[counter]>=0x30){
            //check if all marked fields are geese
            if (board[counter] == 0x39){
                numGeese++;
            }
        } //check if field is hidden only 
        else if (board[counter] >= 0x20){
            //check if all hidden fields are geese
            if (board[counter] == 0x29){
                numGeese++;
            }
        }
    }
    //std::cout << "numGeese" << numGeese << std::endl;
    //std::cout << "checkGeese" << checkGeese << std::endl;

    if (checkGeese == numGeese){
        return true;
    } else{
        return false;
    }
}

void spreadGeese(char *board, std::size_t xdim, std::size_t ydim, unsigned int numGeese){
    
    for (unsigned int geeseCounter{0}; geeseCounter < numGeese; geeseCounter++){
        std::size_t try_pos{0};
        do{
            try_pos = rand() % (xdim *ydim);
        } while (board[try_pos] !=0);
        board[try_pos] = 9;
        //std::cout << "GOOSE AT ARRAY INDEX: " << try_pos << std::endl;
    }
}



//Allocate a char array with xdim by ydim and each element intialized to 0 (array is one dimension)
char *createBoard(std::size_t xdim, std::size_t ydim){
    char *temp_board{new char[xdim*ydim]};
    for (int counter{0}; counter < ydim*xdim; counter++){
       temp_board[counter] = 0x00;
    }

    return temp_board;

}

//Print the board to console
void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    char integer{};
    for (int counter{0}; counter < ydim*xdim; counter++){
        //Check if field is marked
        if (board[counter] & 0x10){
            std::cout << "M";
        }//check if field is hidden 
        else if (board[counter] & 0x20){
            std::cout << "*";
        }//if the field is neither marked or hidden
        else {
            integer = board[counter] + 48;
            std::cout << integer;
        }
        if ((counter+1)%xdim == 0){
            std::cout << "\n";
        }
        
    }
/*     for (int j{}; j<xdim*ydim;j++) {
        std::cout<<"["<<j<<","<<int(board[j])<<"]"<<std::endl; 
    } */
}

//Deallocate and set null pointer to board
void cleanBoard(char *board){
    delete[] board;
    board = nullptr;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    for (int counter{0}; counter < ydim*xdim; counter++){
        if (board[counter] == 0x09){
            //If there is a mr goose at (0,0)
            if(counter == 0){
                if (board[counter+1]!=0x09){
                    //Add one to the geese neighbours at (0,1)
                    board[counter+1] += 0x01;
                } 
                if (board[xdim] != 0x09){
                    //Add one to below the (0,0) field
                    board[xdim] += 0x01;
                }
                if (board[xdim+1]!=0x09){
                //Add one adjacent to (0,0)
                    board[xdim+1] += 0x01;
                }
            } 
            //If there is a mr goose at the top right corner (xdim, 0)
            else if(counter == xdim-1){
                if (board[counter-1]!=0x09){
                    //Add one to the geese neighbours at (xdim-1,0)
                    board[counter-1] += 0x01;
                }
                if (board[(xdim)*2-1]!=0x09){
                    //Add one to below the (xdim,1) field
                    board[(xdim)*2-1] += 0x01;
                }
                if (board[(xdim)*2-2] !=0x09){
                    //Add one adjacent to (xdim,0)
                    board[(xdim)*2-2] += 0x01; 
                }    
            }
            //if there is a mr gooose at the bottom left corner (0,ydim)
            else if(counter == xdim*(ydim-1)){
                if (board[counter+1]!=0x09){
                    //Add one to the geese neighbours at (1,ydim)
                    board[counter+1] += 0x01;
                }
                if (board[counter-xdim]!=0x09){
                    //Add one above
                    board[counter-xdim] += 0x01;
                }
                if (board[counter-xdim+1]!=0x09){
                    //Add one adjacent
                    board[counter-xdim+1] += 0x01;
                }              
            }
            //if there is a mr goose at the bottom right corner (xdim,ydim)
            else if (counter == (xdim*ydim)-1){
                if (board[counter-1]!=0x09){
                    //Add one to the geese neighbours at (xdim-1, ydim)
                    board[counter-1] += 0x01;
                }
                if (board[counter-xdim] !=0x09){
                    //Add one above
                    board[counter-xdim] += 0x01;
                }
                if (board[counter-xdim-1] != 0x09){
                    //Add one adjacent
                    board[counter-xdim-1] += 0x01;
                }
            }
            //if there is a mr goose at the top row (minus the other cases)
            else if (counter < xdim){
                //Add one to the egeese neighbours left and right of the geese
                if (board[counter-1] != 0x09){
                    board[counter-1] += 0x01;
                }
                if (board[counter+1] != 0x09){
                    board[counter+1] += 0x01;
                }
                //Add one to the geese neighbours adjacent and below
                if (board[xdim+counter-1] != 0x09){
                    board[xdim+counter-1] +=0x01;
                }
                if (board[xdim+counter] != 0x09){
                    board[xdim+counter] +=0x01;
                }
                if (board[xdim+counter+1] != 0x09){
                    board[xdim+counter+1] += 0x01;
                }
            }
            //if there is a mr goose at the bottom row
            else if (counter > (xdim*(ydim-1)-1)){
                //Add one to the geese neighbours left and right
                if (board[counter-1] != 0x09){
                    board[counter-1] += 0x01;
                }
                if (board[counter+1] != 0x09){
                    board[counter+1] += 0x01;
                }
                //Add one to the geese neighbours adjacent and above
                if (board[counter-xdim] != 0x09){
                    board[counter-xdim] += 0x01;
                }
                if (board[counter-xdim-1] != 0x09){
                    board[counter-xdim-1] += 0x01; 
                }
                if (board[counter-xdim+1] != 0x09){
                    board[counter-xdim+1] += 0x01;
                }
            }
            //if there is a mr goose on the left most column
            else if ((counter)%(xdim) == 0){
                //Add one above and below
                if (board[counter-xdim]!=0x09){
                    board[counter-xdim] +=0x01;
                }
                if (board[counter+xdim] != 0x09){
                    board[counter+xdim] +=0x01;
                }
                //Add one beside
                if (board[counter+1] != 0x09){
                    board[counter+1]+= 0x01;
                }
                //Add one adjacent
                if (board[counter-xdim+1] != 0x09){
                    board[counter-xdim+1] += 0x01;
                }
                if (board[counter+xdim+1] != 0x09){
                    board[counter+xdim+1] += 0x01;
                }
            }
            //if there is a mr goose on the right most column
            else if ((counter+1)%(xdim)==0){
                //Add one beside
                if (board[counter-1] != 0x09){
                    board[counter-1] += 0x01;
                }
                //Add one above and below
                if (board[counter+xdim] != 0x09){
                    board[counter+xdim] += 0x01;
                }
                if (board[counter-xdim] != 0x09){
                    board[counter-xdim] += 0x01;
                }
                //Add one adjacent
                if (board[counter-xdim-1] != 0x09){
                    board[counter-xdim-1] += 0x01;
                }
                if (board[counter+xdim-1] != 0x09){
                    board[counter+xdim-1] += 0x01;
                }
            }
            //if there is a mr goose every where else
            else {
                //Add one beside
                if (board[counter-1] != 0x09){
                    board[counter-1] += 0x01;
                }
                if (board[counter+1] != 0x09){
                    board[counter+1] += 0x01;
                }
                //Add one above and below
                if (board[counter+xdim] != 0x09){
                    board[counter+xdim] += 0x01;
                }
                if (board[counter-xdim] != 0x09){
                    board[counter-xdim] += 0x01;
                }
                //Add one adjacent
                if (board[counter+xdim+1] != 0x09){
                    board[counter+xdim+1] += 0x01;
                }
                if (board[counter+xdim-1] != 0x09){
                    board[counter+xdim-1] += 0x01;
                }
                if (board[counter-xdim+1] != 0x09){
                    board[counter-xdim+1] += 0x01;
                }
                if (board[counter-xdim-1] != 0x09){
                    board[counter-xdim-1] += 0x01;
                }
            }
        }
    }
}

//sets all elements to 0x20
void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    for (int counter{0}; counter < ydim*xdim; counter++){
       board[counter] += 0x20;
    }
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    for (int counter{0}; counter < ydim*xdim; counter++){
        if (xloc == 0){
               if (counter == yloc*xdim){
                   //check is the board is already marked
                   if (board[yloc*xdim] & 0x10){
                       //unmark the spot
                       board[yloc*xdim] -= 0x10;
                       return 2;
                   } else {
                    board[yloc*xdim] += 0x10;
                    return 0;
                    }
               }
           } else if (yloc==0){
               if (counter == xloc){
                   if (board[xloc] & 0x10){
                       board[xloc] -= 0x10;
                       return 2;
                   } else {
                    board[xloc] += 0x10;
                    return 0;
                   }
               }
           } else if (counter == xloc+yloc*xdim){
               if (board[yloc*xdim+xloc] & 0x10){
                   board[yloc*xdim+xloc] -= 0x10;
                   return 2;
               } else {
                   board[yloc*xdim+xloc] += 0x10;
                   return 0;
               }
           }

    }
    return 2;
}


int main(){
    std::size_t x{}, y{}, xPos{}, yPos{};
    unsigned int numGeese{};
    char action{};
    int markCheck{}, showCheck{};


    std::cout << "Welcome to GesseSpotter!" << std::endl;
    std::cout << "Please enter the x dimension: ";
    std::cin >> x;
    std::cout << "Please enter the y dimension: ";
    std::cin >> y;
    std::cout << "Please enter the number of geese: ";
    std::cin >> numGeese;

    char *board{};
    
    board = createBoard(x,y);

    spreadGeese(board, x, y, numGeese);

    computeNeighbors(board, x, y);

    //printBoard(board, x, y);

    hideBoard(board,x,y);

    while (action != 'Q')
    {    
        
        printBoard(board, x, y);
        std::cout << "Please enter the action ([S]how; [M]ark; [R]estart; [Q]uit): ";
        std::cin >> action;

        if (action == 'M'){
            std::cout << "Please enter the x location: ";
            std::cin >> xPos;
            std::cout << "Please enter the y location: ";
            std::cin >> yPos;
            markCheck = mark(board, x, y, xPos, yPos);
        }
        if (action == 'S'){
            std::cout << "Please enter the x location: ";
            std::cin >> xPos;
            std::cout << "Please enter the y location: ";
            std::cin >> yPos;
            showCheck = reveal(board, x, y, xPos, yPos);
            std::cout << showCheck;
        }
        std::cout << isGameWon(board, x, y) << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }  
    return 0; 
} 