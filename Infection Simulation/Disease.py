# By submitting this assignment, I agree to the following:
#  "Aggies do not lie, cheat, or steal, or tolerate those who do"
#  "I have not given or received any unauthorized aid on this assignment"
#
# Name:        Marcel Thio, Sunjeeth Chandramohan, Reagan Schwartz
# Section:     503
# Assignment:  Activity3
# Date:        8 December 2018

import random as ran

def parameters(num):
    '''
    Set up the parameters values
    :param num: how many people is it for
    :return: the 4 parameters
    '''
    res = []
    rec = []
    act = []
    tra = []
    for x in range(num):
        # resistance probability
        res.append(ran.uniform(.5,.75))
        # recovery days of a person
        rec.append(ran.randint(4, 10))
        # amount of people a person comes to contact with in a single day
        act.append(ran.randint(5, 30))
        # Transmission probability
        tra.append(ran.uniform(.45, .75))
    return res, rec, act, tra


def act2para(num):
    '''
    Set up the parameters values
    :param num: how many people is it for
    :return: the 4 parameters
    '''
    res = []
    rec = []
    act = []
    tra = []
    tra2 = []
    for x in range(num):
        # resistance probability
        res.append(ran.uniform(.5,.75))
        # recovery days of a person
        rec.append(ran.randint(4, 10))
        # amount of people a person comes to contact with in a single day
        act.append(ran.randint(5, 30))
        # Transmission probability
        tra.append(ran.uniform(.45, .75))
        # Transmission probability with friends
        tra2.append(ran.uniform(.65, .95))
    return res, rec, act, tra, tra2

def parameters2(num):
    '''
    Set up the parameters values
    :param num: how many people is it for
    :return: the 4 parameters
    '''
    res = []
    rec = []
    act = []
    tra = []
    for x in range(num):
        # resistance probability
        res.append(ran.uniform(.5,.75))
        # recovery days of a person
        rec.append(ran.randint(4, 10))
        # amount of people a person comes to contact with in a single day
        act.append(ran.randint(1, 10))
        # Transmission probability
        tra.append(ran.uniform(.45, .75))
    return res, rec, act, tra


def new_infected(new_inf,inf,healthy):
    '''
    add newly infected to ifected list and remove from healthu
    :param new_inf: newly infected
    :param inf: infected indexes
    :param healthy: never infected
    :return: infected and healthy lists
    '''
    # add newly infected
    for index in new_inf:
        inf.append(index)
        healthy.remove(index)
    return inf,healthy


def immunity(rec,inf,immun):
    '''
    Checks if the infected is now immune
    :param rec: recovery period
    :param inf: infected indexes
    :param immun: immune indexes
    :return: updated list of infected or immune indexes
    '''
    new_immun = []
    # add newly immune
    for index in inf:
        if rec[index] == 0:
            new_immun.append(index)
    for index in new_immun:
        inf.remove(index)
        immun.append(index)
    return inf, immun


def recovery(inf,rec):
    '''
    Just update recovery period
    :param inf: infected index
    :param rec: recovery days if infected
    :return: updated recovery days
    '''
    # go throught and subtract 1 from recovery of infected
    for index in inf:
        rec[index] = rec[index] - 1
    return rec


def infect(inf, res, act, tra, immun, tra2):
    '''
    simulate infection
    :param inf: list of infected
    :param res: resistance parameter
    :param act: how active a given person is
    :param tra: probability of transmittance
    :param immun: list of immune persons
    :return: index of new infected
    '''
    # newly infected
    newly_inf = []
    for index in inf:
        # simulate interactions with class
        for i in range(0, act[index]):
            # people index that are interacted with
            interact_p = ran.randint(0,len(res)-1)
            # check if other person is normal i.e. not immune or infected
            if not (interact_p in immun) and not (interact_p in inf) and not(interact_p in newly_inf):
                # checks if person is infected
                if is_infected(res,tra,index,interact_p):
                    newly_inf.append(interact_p)
        # close friends
        if tra2:
            for i in range(0, 5):
                # people index that are interacted with
                interact_p = ran.randint(0,len(res)-1)
                # check if other person is normal i.e. not immune or infected
                if not (interact_p in immun) and not (interact_p in inf) and not(interact_p in newly_inf):
                    # checks if person is infected
                    if is_infected(res,tra2,index,interact_p):
                        newly_inf.append(interact_p)
    return newly_inf


def is_infected(res,tra,inf_index,nor_index):
    '''
    Checks if user is infected
    :param res: resistance values
    :param tra:transmittance probabilities
    :param inf_index: the infected index
    :param nor_index: the person in contact index
    :return: true if infected false if not
    '''
    # checks if transmission occurs
    if tra[inf_index] >= ran.random():
        # checks if resistance failed
        if res[nor_index] < ran.random():
            return True
    return False

