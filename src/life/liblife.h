#define LIFE_HISTORY_SIZE 10
typedef struct {
    int x;
    int y;
    int z;
    int generation;
    int*** alive;
    int*** neighbors;
    // birth and death are tracked separately from history data to keep the features independent
    int*** born;
    int*** died; 

    // the earliest generation stored in history
    int history_first_gen;
    int history_pos;
    int history_count;
    int*** history[LIFE_HISTORY_SIZE];
} life_grid;

typedef struct {
    int x;
    int y;
    int z;
    int*** alive;
} life_pattern;


#ifdef __cplusplus                                                           
extern "C" {
#endif

life_grid* life_init(int x, int y, int z);
int life_set_alive(life_grid* grid , int x, int y, int z);
int life_set_dead(life_grid* grid , int x, int y, int z);
int life_is_alive(life_grid* grid , int x, int y, int z);
int life_just_died(life_grid* grid , int x, int y, int z);
int life_print(life_grid* grid);
int _life_calc_neighbors(life_grid* grid);
int _life_calc_neighbors_subgrid(life_grid* grid);
int _life_check_neighbors_for_z(life_grid* grid, int x, int y, int z, int zslice);
int life_next_gen(life_grid* grid);
int life_prev_gen(life_grid* grid);
int life_read_lif(life_grid* grid, char* filename);
int _life_record_history(life_grid* grid);
int*** _life_array_alloc(int x, int y, int z);
#ifdef __cplusplus
}
#endif

