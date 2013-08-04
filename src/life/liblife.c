#include "liblife.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h>

life_grid* life_init(int x, int y, int z){
    int i;

    life_grid* grid;
    grid = (life_grid*) malloc(sizeof(life_grid));
    grid->generation = 0;

    // enforce a minimum dimension size of 1
    if(x == 0) x = 1;
    if(y == 0) y = 1;
    if(z == 0) z = 1;
    grid->x = x;
    grid->y = y;
    grid->z = z;

    // Allocate the mutidimensional arrays
    grid->alive = _life_array_alloc(x,y,z);
    grid->neighbors = _life_array_alloc(x,y,z);
    grid->born = _life_array_alloc(x,y,z);
    grid->died = _life_array_alloc(x,y,z);

    grid->history_count = 0;
    grid->history_pos = 0;

    // pre-allocate the history
    for(i = 0; i < LIFE_HISTORY_SIZE; i++){
        grid->history[i] = _life_array_alloc(x,y,z);
    }

    return grid;
}

int*** _life_array_alloc(int x, int y, int z){

    int i, j, k;
    int*** array; 
    // Allocate the 3d array
    array = (int***) malloc(x * sizeof(int **));
    for(i = 0; i < x; i++){
        array[i] = (int**) malloc(y * sizeof(int *));
        for(j = 0; j < y; j++){
            array[i][j] = (int*) malloc(z * sizeof(int));
            for(k = 0; k < z; k++){
                //todo use memset instead
                array[i][j][k] = 0;
            }
        }
    }
    return array;
}

int _life_calc_neighbors(life_grid* grid){
	return _life_calc_neighbors_subgrid(grid);
}


// 2n
int _life_calc_neighbors_subgrid(life_grid* grid){
    int x, y, z;

   //Reset all neighbor counts to 0
   // n
    for(z = 0; z < grid->z; z++){
        for(y = 0; y < grid->y; y++){
            for(x = 0; x < grid->x; x++){
               grid->neighbors[x][y][z] = 0;
            }
        }
    }

    // Loop through and count neighbors
    // n

    for(z = 0; z < grid->z; z++){
        for(y = 0; y < grid->y; y++){
            for(x = 0; x < grid->x; x++){
		_life_check_neighbors_for_z(grid, x, y, z,z);
		if(z < grid->z - 1){
		//	_life_check_neighbors_for_z(grid, x, y, z,z+1);
		}
		if(z > 0){
		//	_life_check_neighbors_for_z(grid, x, y, z,z-1);
		}
            }
        }
    }
    return 1;
}

int _life_check_neighbors_for_z(life_grid* grid, int x, int y, int z, int zslice){
               if(y < grid->y - 1){
                grid->neighbors[x][y][z] += grid->alive[x][y+1][zslice];
                // above and right
                if(x < grid->x - 1){
                    grid->neighbors[x][y][z] += grid->alive[x+1][y+1][zslice];
                }
                // above and left
                if(x > 0){
                    grid->neighbors[x][y][z] += grid->alive[x-1][y+1][zslice];
                } 
               } 
               //below
               if(y > 0){
                grid->neighbors[x][y][z] += grid->alive[x][y-1][zslice];
                // below and right
                if(x < grid->x - 1){
                    grid->neighbors[x][y][z] += grid->alive[x+1][y-1][zslice];
                }
                // below and left
                if(x > 0){
                    grid->neighbors[x][y][z] += grid->alive[x-1][y-1][zslice];
                } 
               } 
               //right
               if(x < grid->x - 1){
                grid->neighbors[x][y][z] += grid->alive[x+1][y][zslice];
               } 
               //left
               if(x > 0){
                grid->neighbors[x][y][z] += grid->alive[x-1][y][zslice];
               } 
}

int _life_record_history(life_grid* grid){
   // printf("history count: %d, pos: %d\n",grid->history_count, grid->history_pos);
    memcpy(grid->history[grid->history_pos], grid->alive, 
	   (grid->x * grid->y * grid->z * sizeof(int)) + (grid->x * sizeof(int**)) + (grid->x * grid->y * sizeof(int*))*4 );

    grid->history_pos++;
    if(grid->history_pos > LIFE_HISTORY_SIZE - 1){
        grid->history_pos = 0;
    }
    if(grid->history_count < LIFE_HISTORY_SIZE - 1){
        grid->history_count++;
    }

    return 1;
}

int life_prev_gen(life_grid* grid){
    int offset = 1;
    
    if(grid->history_count != 0){
        grid->history_pos--;
        grid->history_count--;
        if(grid->history_pos == -1){
          if(grid->history_count != 0){
            grid->history_pos = LIFE_HISTORY_SIZE - 1;
          }
          else{
            grid->history_pos = 0;
          }
        }
    }

   // printf("going back to pos generation: %d, count: %d, pos: %d\n",grid->generation, grid->history_count, grid->history_pos);
    if(grid->generation > 0){
        memcpy(grid->alive, grid->history[grid->history_pos], (grid->x * grid->y * grid->z * sizeof(int)) + (grid->x * sizeof(int**)) + (grid->x * grid->y * sizeof(int*))*4 );
        grid->generation--;
        _life_calc_neighbors(grid);
    }
    else{
        return 0;
    }
    return 1;
}

int life_next_gen(life_grid* grid){
    int x, y, z;
	int el = 2;
	int eh = 3;
	int fl = 3;
	int fh = 3;

    // history is breaking the z dimension
    //_life_record_history(grid);
    grid->generation++;
    _life_calc_neighbors(grid);

	//exist low, exist high, fertile low, fertile high
	//5766 or 4555 for 3d
	//2333 regular

	
    for(z = 0; z < grid->z; z++){
        for(y = 0; y < grid->y; y++){
            for(x = 0; x < grid->x; x++){
              grid->died[x][y][z] = 0;
              if( grid->neighbors[x][y][z] >= fl && grid->neighbors[x][y][z] <= fh ){
                    grid->alive[x][y][z] = 1;  
                    // if none, born
               }
              else if(grid->alive[x][y][z] && (grid->neighbors[x][y][z] >= el && grid->neighbors[x][y][z] <= eh)){
                    // no change
              }
              else{
                    // if it was alive, record its death
                    grid->died[x][y][z] = grid->alive[x][y][z];

                    // die of lonelyness or crowding
                    grid->alive[x][y][z] = 0;  
              }
            }
        }
    }
   //Why do I calc before and after?
    _life_calc_neighbors(grid);
    
}

int life_set_alive(life_grid* grid , int x, int y, int z){
    // Check bounds
    if(x >= grid->x || y >= grid->y || z >= grid->z || x < 0 || y < 0 || z < 0){
        return 0;
    }
    grid->alive[x][y][z] = 1;
    return 1;
}

int life_set_dead(life_grid* grid , int x, int y, int z){
    // Check bounds
    if(x >= grid->x || y >= grid->y || z >= grid->z || x < 0 || y < 0 || z < 0){
        return 0;
    }
    grid->alive[x][y][z] = 0;
    return 1;
}

int life_just_died(life_grid* grid , int x, int y, int z){
    // Check bounds
    if(x >= grid->x || y >= grid->y || z >= grid->z || x < 0 || y < 0 || z < 0){
        return 0;
    }
    return grid->died[x][y][z];
}

int life_is_alive(life_grid* grid , int x, int y, int z){
    // Check bounds
    if(x >= grid->x || y >= grid->y || z >= grid->z || x < 0 || y < 0 || z < 0){
        return 0;
    }
    return grid->alive[x][y][z];
}

int life_print(life_grid* grid){
    int iy, ix, iz;
    printf("\nThe grid is %d by %d by %d\n",grid->x, grid->y, grid->z);
    for(iz = 0; iz < grid->z; iz++){
        printf("z-slice %d\n",iz);
        for(iy = 0; iy < grid->y; iy++){
                for(ix = 0; ix < grid->x; ix++){
                //printf("|%d(%d)",grid->alive[ix][iy][iz], grid->neighbors[ix][iy][iz]);
		printf("|%d",grid->alive[ix][iy][iz], grid->neighbors[ix][iy][iz]);
            }
            printf("\n");
        }
    }

}

int life_read_lif(life_grid* grid, char* filename){
	FILE* pattern_file;
	char buffer;
	char num_buffer[10];
	int num_buffer_pos = 0;
	//int found_x = 0;
	//int found_y = 0;
	int start_x, start_y;
	int base_x, base_y;
	int in_comment = 0;
	int in_position_line = 0;
	int position_sign = 1;
	int in_cell_line = 0;
	int line_start = 0;
	int x = 0;
	int y = 0;
	long file_size;
	pattern_file = fopen(filename, "r");
	//size_t result;

	start_x = grid->x / 2;
	start_y = grid->y / 2;
	base_x = base_y = 0;
	//start_x = 13; start_y = 3;
	x = start_x + base_x;
	y = start_y + base_y;

  	if (pattern_file==NULL) {
		fputs ("File error",stderr); 
		return 0;
	}
	
	do{
		buffer = fgetc(pattern_file);

		if(line_start){
			if(buffer != '#'){
				in_cell_line = 1;
			}
			else{
				// Get the line type character
				buffer = fgetc(pattern_file);
				if(buffer == 'P'){
					in_position_line = 1;
					//Trim the space after the line type character
					buffer = fgetc(pattern_file);
				}
			}
		}
		
		if(in_position_line){
			if(isdigit(buffer)) {
				num_buffer[num_buffer_pos] = buffer;
				num_buffer_pos++;
				num_buffer[num_buffer_pos] = '\0';
			}
			else if(buffer == ' ') {
				base_x = position_sign * atoi(num_buffer);
				//printf("%s=%d num\n",num_buffer, position_sign * atoi(num_buffer));
				num_buffer_pos = 0;
				position_sign = 1;
			}
			else if(buffer == '-') {
				position_sign = -1;
			}
		}

		// Add cells and increment the x,y cursors
		if(in_cell_line){
			if(buffer == '.'){
				x++;
			}
			else if(buffer == '*'){
				//printf("Setting alive: %d, %d\n",x,y);
				life_set_alive(grid, x,y,0);
				x++;
			}
			else if(buffer == '\n'){
				y++;
				x = start_x + base_x;
				
			}
		}

		line_start = 0;
		if(buffer == '\n'){
			if(in_position_line){
				base_y  = position_sign * atoi(num_buffer);
				
				//printf("base_y: %d, start_y: %d, y: %d\n",base_y, start_y, y);
				num_buffer_pos = 0;
				position_sign = 1;
				x = start_x + base_x;
				y = base_y + start_y;
			}
			line_start = 1;
			in_cell_line = 0;
			in_position_line = 0;
		}
	
	}while(buffer != EOF);


	//printf("buffer: %s\n",buffer);
	fclose(pattern_file);
	


}
