NULLRCB = {
    "request_id":0,
    "arrival_timestamp":0,
    "cylinder":0,
    "address":0,
    "process_id":0
}



def handle_request_arrival_fcfs(request_queue, current_request, new_request, timestamp):
    if current_request["process_id"] == 0:
        return new_request
    else:
        request_queue.append(new_request)
        return current_request



def handle_request_completion_fcfs(request_queue):
    if len(request_queue) == 0:
        return NULLRCB
    else:
        shortest = 99999
        elem = NULLRCB
        for req in request_queue:
            if req["arrival_timestamp"]< shortest:
                shortest = req["arrival_timestamp"]
                elem = req
    request_queue.remove(elem)
    return elem


  
 
def handle_request_arrival_sstf(request_queue, current_request, new_request, timestamp):  
    if current_request["process_id"] == 0:
        return new_request
    else:
        request_queue.append(new_request)
        return current_request

def handle_request_completion_sstf(request_queue, current_cylinder):
    if len(request_queue) == 0:
        return NULLRCB
    shortest = 99999
    elem = NULLRCB
    for req in request_queue:
        diff =abs(req["cylinder"] - current_cylinder)
        if diff < shortest:
            shortest = diff
            elem = req
    request_queue.remove(elem)
    return elem

 
def handle_request_arrival_look(request_queue, current_request, new_request, timestamp):  
    if current_request["process_id"] == 0:
        return new_request
    else:
        request_queue.append(new_request)
        return current_request


def handle_request_completion_look(request_queue, current_cylinder, direction):
    if len(request_queue) == 0:
        return NULLRCB

    locyl,hicyl,eqcyl = 0,0,0
    hilst,lolst,eqlst = [],[],[]
    for req in request_queue:
        if req["cylinder"] < current_cylinder:
            locyl  +=1
            lolst.append(req)
        if req["cylinder"] > current_cylinder:
            hicyl +=1
            hilst.append(req)
        if req["cylinder"] == current_cylinder:
            eqcyl +=1
            eqlst.append(req)
    if eqcyl >0:
        samecyl = []
        for req in request_queue:   #same cyl queue
            if req["cylinder"] == current_cylinder:
                samecyl.append(req)
        smallest = 999999
        elem = NULLRCB
        for reqs in samecyl: #finds smallest
            if reqs["arrival_timestamp"] < smallest:
                smallest = reqs["arrival_timestamp"]
                elem = reqs
        request_queue.remove(elem)
        return elem
    else:
        ans = NULLRCB
        if direction == 1:
            if hicyl >0:
                hiclosest = abs(current_cylinder - hilst[0]['cylinder'])
                for hireq in hilst:
                    if abs(hireq["cylinder"] - current_cylinder) <= hiclosest:
                        ans = hireq
            else:
                hiclosest = abs(current_cylinder - hilst[0]['cylinder'])
                for hireq in request_queue:
                    if abs(hireq["cylinder"] - current_cylinder) <= hiclosest:
                        ans = hireq
        if direction == 0:
            if locyl >0:
                loclosest = abs(current_cylinder - lolst[0]['cylinder'])
                for loreq in lolst:
                    if abs(loreq["cylinder"] - current_cylinder) <= loclosest:
                        ans = loreq
            else:
                loclosest = abs(current_cylinder - request_queue[0]['cylinder'])
                for loreq in request_queue:
                    if abs(loreq["cylinder"] - current_cylinder) <= loclosest:
                        ans = loreq
        request_queue.remove(ans)
        return ans







request_queue = []

q1 =  {
        "request_id":1,
        "arrival_timestamp":52,
        "cylinder":58,
        "address":58,
        "process_id":1
    }

q2=  {
        "request_id":2,
        "arrival_timestamp": 51,
        "cylinder": 58,
        "address":58,
        "process_id":2
    }

q3 =  {
        "request_id":3,
        "arrival_timestamp":53,
        "cylinder":58,
        "address":58,
        "process_id":3
    }

request_queue.append(q1)
request_queue.append(q2)
request_queue.append(q3)




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
    

ans = handle_request_completion_look(request_queue,58,1)
print(ans)
