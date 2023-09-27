'''
file: metro_lines.py
author: umair Khan
date: 05/18/22
section: 33
email: ukhan5@umbc.edu
description: makes a working train station
'''
# all constants
stations = {}
print_stations = []
trains = []
connects = []
train_line = []
train_desti = []
train_to_station = {}
train_route = {}
route_and_start = {}
value_list = []
route_list = []
split_list = []
emp_list = []
plan_list = []
plan_emp_list = []

# display trains command
def train_display(user_input):
    i = 0
    key_list = list(train_route)
    list_append = list(train_route.values())
    route_append = list(train_to_station.values())
    value_list.append(list_append)
    route_list.append(route_append)
    while i < len(train_route.keys()):
        key_index = key_list[i]
        value_index = list_append[i]
        route_index = route_append[i]
        print(f'*** Information for Train {key_index} ***'
              f'    Line: {value_index}'
              f'    Current Position: {route_index}')
        i += 1
    return value_list, route_list

# runs plan trip
def plan_trip(user_input):
    route_desti = route_and_start
    stationss = stations
    route_train = train_route
    train_station = train_to_station
    train_dash = train_line
    destination = train_desti
    trial_list = plan_emp_list
    key_list = list(route_desti.keys())
    val_list = list(route_desti.values())
    i = 0
    j = 0
    while i < len(route_desti):
        str_list = train_dash[i]
        split = str_list.split('-')
        plan_list.append(split)
        if user_input[2] == plan_list[i][j]:
            if user_input[3] == plan_list[i][j + 1]:
                print(f'Start on the {connects[i]} --> {plan_list[i][j + 1]}')
            else:
                print(f'Start on the {train_line[0]} --> {train_desti[0]} at {train_desti[1]} transfer from the {train_line[0]} line to the {train_line[2]} line --> {print_stations[3]}')
                i += 4


# runs step command
def step():
    train_dash = train_line
    destination = train_desti
    trial_list = emp_list
    trial_list.clear()
    i = 0
    j = 0
    while i < len(train_dash):
        str_list = train_dash[i]
        split = str_list.split('-')
        split_list.append(split)
        if destination[i] == split_list[i][j]:
            trial_list.append(split_list[i][j + 1])
            print(f'{trains[i]} has moved from {destination[i]} to {trial_list[i]}')
            i += 1
        elif destination[i] != split_list[i][j]:
            if split_list[i][j + 1] == destination[i]:
                trial_list.append(split_list[i][j])
                print(f'{trains[i]} has moved from {destination[i]} to {trial_list[i]}')
                i += 1
    i = 0
    while i < len(train_dash):
        train_dash[i] = f'{split_list[i][j + 1]}-{split_list[i][j]}'
        destination[i] = f'{split_list[i][j + 1]}'
        i += 1

# where user inputs and lists are made that are used throughout the porjects
def create_and_connect():
    user_input = input('>>> ').split(' ')
    counter = 0
    while user_input[0] != 'exit':
        if user_input[0] == 'create' and user_input[1] == 'station':
            print_stations.append(user_input[2])
            stations[user_input[2]] = counter
            counter += 1
            user_input = input('>>> ').split(' ')
        elif user_input[0] == 'connect':
            connects.append(user_input[4])
            user_input = input('>>> ').split(' ')
        elif user_input[0] == 'create' and user_input[1] == 'train':
            trains.append(user_input[2])
            train_line.append(user_input[3])
            train_desti.append(user_input[4])
            train_route[user_input[2]] = user_input[3]
            train_to_station[user_input[2]] = user_input[4]
            route_and_start[user_input[3]] = user_input[4]

            user_input = input('>>> ').split(' ')
        elif user_input[0] == 'display' and user_input[1] == 'stations':
            print(print_stations)
            user_input = input('>>> ').split(' ')
        elif user_input[0] == 'display' and user_input[1] == 'trains':
            train_display(user_input)
            user_input = input('>>> ').split(' ')

        elif user_input[0] == 'plan':
            plan_trip(user_input)
            user_input = input('>>> ').split(' ')
        elif user_input[0] == 'step':
            step()
            user_input = input('>>> ').split(' ')

    return user_input


if __name__ == '__main__':
    create_and_connect()
