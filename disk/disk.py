NULLRCB = {
    "request_id":0,
    "arrival_timestamp":0,
    "cylinder":0,
    "address":0,
    "process_id":0
}



def handle_request_arrival_fcfs(request_queue, current_request, new_request, timestamp):
    if len(set(current_request.values())) == 0:
        return new_request
    else:
        request_queue.append(new_request)
        return current_request



def handle_request_completion_fcfs(request_queue):
    if len(request_queue):
        return NULLRCB
    else:
        shortest = 99999
        elem
        for req in request_queue:
            if req["arrival_timestamp"]< shortest:
                shortest = req["arrival_timestamp"]
                elem = req
    request_queue.remove(elem)
    return elem


  
 
def handle_request_arrival_sstf(request_queue, current_request, new_request, timestamp):  
    if len(set(current_request.values())) == 0:
        return new_request
    else:
        request_queue.append(new_request)
        return current_request

def handle_request_completion_sstf(request_queue, current_cylinder):
    if len(request_queue) == 0:
        return NULLRCB
    
 
def handle_request_arrival_look(request_queue, current_request, new_request, timestamp):  
  pass

def handle_request_completion_look(request_queue, current_cylinder, direction):
  pass



if __name__ == "main":
    request_queue = [0]
    current_request =  {
    "request_id":51,
    "arrival_timestamp":1,
    "cylinder":53,
    "address":53,
    "process_id":51
    }
    new_request =  {
    "request_id":52,
    "arrival_timestamp":2,
    "cylinder":54,
    "address":54,
    "process_id":52
    }
    timestamp = 2
    

ans = handle_request_arrival_fcfs(request_queue, current_request, new_request, timestamp)
print(ans)
