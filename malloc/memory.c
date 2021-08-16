#include "oslabs.h"




struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id);  
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id);  
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id);  
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address); 

struct MEMORY_BLOCK NULLBLOCK = {0,0,0,0};


/*
t finds the candidate memory blocks that can be allocated and chooses the one whose size is closest to the requested size.
 If the free block found is exactly of the same size as the requested size, the method updates the process id to allocate it'
  and returns this memory block. If the free block found is larger than the requested size, the block is split into two pieces
  - the first piece allocated and the second piece becoming a free block in the memory map. Thus, the method may alter the memory
   map appropriately. Note that if there is no free block of memory (in the memory map) that is at least as large as the requested 
   size, the method returns the NULLBLOCK. 
    */
struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
        int i,difference,closest[*map_cnt];//saves index with closest value greater than req_size using difference var
        int lowest = 99999;
        /*
        for(i=0;i<*map_cnt;i++){
            difference =  memory_map[i].segment_size - request_size;
            closest[i] = difference;
        }
        int index;
        for(i=0;i<*map_cnt;i++){
            if(closest[i] < lowest)
                lowest = closest[i];
                index = i;
        }

        */
       for(i=0;i<*map_cnt;i++){
           if(memory_map[i].segment_size >= request_size){
                difference = memory_map[i].segment_size - request_size;
                closest[i] = difference;
                }
            else{
                closest[i] = -1;
            }
       }

       int index;
       for(i=0;i<*map_cnt;i++){
           if(closest[i] != -1){
               if(closest[i] <=lowest){
               lowest = closest[i];
               index = i;
               }
           }
       }

        struct MEMORY_BLOCK elem = memory_map[index]; 
        if(elem.segment_size ==request_size ){
            elem.process_id = process_id;
            return elem;
        }
        else if (request_size <elem.segment_size){
           struct MEMORY_BLOCK split1,split2;
           
           split1.process_id = process_id;
           split1.segment_size = request_size;
           split1.start_address = elem.start_address;
           split1.end_address = elem.start_address + request_size-1;

           split2.segment_size = elem.segment_size - split1.segment_size;
           split2.process_id =0;
           split2.start_address = split1.end_address+1;
           split2.end_address = split2.start_address + split2.segment_size-1;
           memory_map[*map_cnt] = split2;
           memory_map[index] = split1;
           *map_cnt += 1;
           return split1;
        }
        
        else
        return NULLBLOCK; 

    }


/*This method allocates memory according to the First Fit scheme. The method is given the process id of the requesting process, 
size of the memory being requested, and the memory map. It finds the first (lowest starting address) free memory block whose size
 is at least as large as the requested size. If the free block found is exactly of the same size as the requested size, the method
  updates the process id to allocate it and returns this memory block. If the free block found is larger than the requested size, 
  the block is split into two pieces - the first piece allocated and the second piece becoming a free block in the memory map. Thus,
   the method may alter the memory map appropriately. Note that if there is no free block of memory (in the memory map) that is at
    least as large as the requested size, the method returns the NULLBLOCK.
    */

   //fix first fit
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
 int i,closest_size;
    struct MEMORY_BLOCK answer = NULLBLOCK;
    for(i =0;i<*map_cnt;i++){

        struct MEMORY_BLOCK elem = memory_map[i];

        if(request_size == elem.segment_size){
           elem.process_id = process_id;
           return elem; 
        }
        else if(request_size < elem.segment_size){
           struct MEMORY_BLOCK split1,split2;
           split1.process_id = process_id;
           split1.segment_size = request_size;
           split1.start_address = elem.start_address;
           split1.end_address = elem.start_address + request_size-1;

           split2.segment_size = elem.segment_size - split1.segment_size;
           split2.process_id =0;
           split2.start_address = split1.end_address+1;
           split2.end_address = split2.start_address + split2.segment_size-1;
           memory_map[*map_cnt] = split2;
           memory_map[i] = split1;
           *map_cnt += 1;
           return split1;
        }
        else
        return NULLBLOCK; 

    }

    return NULLBLOCK;

}

/*This method allocates memory according to the Worst Fit scheme. The method is given the process id of the requesting process,
 size of the memory being requested, and the memory map. It finds the candidate memory blocks that can be allocated and chooses
  the largest among these blocks. If the free block found is exactly of the same size as the requested size, the method updates
   the process id to allocate it and returns this memory block. If the free block found is larger than the requested size, the
    block is split into two pieces - the first piece allocated and the second piece becoming a free block in the memory map. Thus,
     the method may alter the memory map appropriately. Note that if there is no free block of memory (in the memory map) that is at
      least as large as the requested size, the method returns the NULLBLOCK.*/

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
int i,largest =-1,pos;
for(i =0;i<*map_cnt;i++){
if(memory_map[i].segment_size > largest){
    largest = memory_map[i].segment_size;
    pos = i;
}
struct MEMORY_BLOCK elem = memory_map[i];

if(request_size == elem.segment_size){
           elem.process_id = process_id;
           return elem; 
        }
        else if(request_size < elem.segment_size){
           struct MEMORY_BLOCK split1,split2;
           split1.process_id = process_id;
           split1.segment_size = request_size;
           split1.start_address = elem.start_address;
           split1.end_address = elem.start_address + request_size-1;

           split2.segment_size = elem.segment_size - split1.segment_size;
           split2.process_id =0;
           split2.start_address = split1.end_address+1;
           split2.end_address = split2.start_address + split2.segment_size-1;
           memory_map[*map_cnt] = split2;
           memory_map[i] = split1;
           *map_cnt += 1;
           return split1;
        }
        else
        return NULLBLOCK; 

    }

return NULLBLOCK;

}

/*This method allocates memory according to the Next Fit scheme. The method is given the process id of the requesting process,
size of the memory requested, the memory map, and the address of the last block allocated. It finds the first (lowest starting address)
 free memory block, greater than or equal to the previously allocated block address, whose size is at least as the requested size.
  If the free block found is exactly of the same size as the requested size, the method updates the process id to allocate it and
   returns this memory block. If the free block found is larger than the requested size, the block is split into two pieces - the
    first piece allocated and the second piece becoming a free block in the memory map. Thus, the method may alter the memory map
     appropriately. Note that if there is no free block of memory (in the memory map) that is at least as large as the requested
      size, the method returns the NULLBLOCK.*/
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address){
int end;
int pos,lowest;
for(end=0;end< *map_cnt;end++){
    struct MEMORY_BLOCK elem = memory_map[end];
    if(elem.end_address >= last_address ){
        if(elem.segment_size == request_size){
            elem.process_id = process_id;
        }
        else if(elem.segment_size > request_size){
            struct MEMORY_BLOCK split1,split2;
           split1.process_id = process_id;
           split1.segment_size = request_size;
           split1.start_address = elem.start_address;
           split1.end_address = elem.start_address + request_size-1;

           split2.segment_size = elem.segment_size - split1.segment_size;
           split2.process_id =0;
           split2.start_address = split1.end_address+1;
           split2.end_address = split2.start_address + split2.segment_size-1;
           memory_map[*map_cnt] = split2;
           memory_map[end] = split1;
           *map_cnt += 1;
           return split1;
        }
        else
        return NULLBLOCK; 

    }
}

return NULLBLOCK;

}



/* 
This method releases a memory block. Accordingly, it modifies the memory map passed in. Specifically, it marks the released block
 of memory as free and then it merges that block with adjacent free blocks if any. That is, if the memory block adjacent to the
  newly released block is free, the memory map is altered to reduce the number of memory blocks by one and the ending address
   (and the size) of the previous free block extended. Note that the method does not have any explicit return value and
    instead modifies the memory map passed in. 
*/
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt){
    int i, pos =0;

    for(i =0;i<*map_cnt;i++){
        if(memory_map[i].start_address == freed_block.start_address && memory_map[i].end_address == freed_block.end_address){
            pos =i;
            break;
        }
    }
    memory_map[pos].process_id=0;
    if(pos-1 >=0){ //shift elems down 1 and add end addr and size
        if(memory_map[pos-1].process_id == 0){
            memory_map[pos].start_address = memory_map[pos-1].start_address;
            memory_map[pos].segment_size += memory_map[pos-1].segment_size;
            int i;
            for(i=pos-1;i<*map_cnt-1;i++){
                memory_map[i] = memory_map[i+1];  
            }
            *map_cnt-=1;
        }
    }
    pos-=1;
    if(pos+1 < *map_cnt){
        if(memory_map[pos+1].process_id ==0){
            memory_map[pos].end_address = memory_map[pos+1].end_address;
            memory_map[pos].segment_size += memory_map[pos+1].segment_size;
            int i;
            for(i = pos+1;i<*map_cnt-1;i++){
                memory_map[i] = memory_map[i+1];
            }
        *map_cnt-=1;
        }
    }
}


int main(){

/*struct MEMORY_BLOCK map[10];
struct MEMORY_BLOCK map0 = {0,7, 8, 12};
struct MEMORY_BLOCK map1 = {8,15,8,0};
struct MEMORY_BLOCK map2 = {16,23,8,13};
struct MEMORY_BLOCK map3 = {24,27,4,0};
struct MEMORY_BLOCK map4 = {28,29,2,11};
map[0] = map0;
map[1] = map1;
map[2] = map2;
map[3] = map3;
map[4] = map4;
int mapcnt = 5;
*/

//release_memory(map[2],map,&mapcnt);

int count = 4;
int size = 30;
int id = 30;
struct MEMORY_BLOCK extra[10] = {{0,19,20,10},{20,39,20,0},
                                {40,49,10,20},{50,1023,974,30}};
struct MEMORY_BLOCK ans = best_fit_allocate(size,extra,&count,id);


return 0;
//-----------------------------------------------------------------


}


