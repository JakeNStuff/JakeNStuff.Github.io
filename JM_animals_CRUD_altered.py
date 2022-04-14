from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):

    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password):
        #Cleaned up and added confirmation of database connection
        self.client = MongoClient('mongodb://%s:%s@localhost:37300/AAC' % (user, password))
        self.database = self.client['AAC']
        print("Connected to Database")
        
#CREATE        
# Method to implement the C in CRUD.
    def create(self, data):
    ###########################################################
    #Added try argument and cleaned this up to make more sense. 
    ###########################################################
        try:
            if data is not None:
                # data should be dictionary            
                insert = self.AAC.animals.insert(data)  
                print(insert)
                return True            
            else:
                #Raise ERROR
                raise Exception("Nothing to save, data is empty")        
            except:
                return False

#READ
# Method to implement the R in CRUD.
    def read(self,target):
    ###########################################################
    #Added try argument and cleaned this up to make more sense. 
    ###########################################################
        try:
            if target is not None:
                read_result = list(self.database.animals.find(target, {"_id": False}))
                return read_result
            else:
                raise Exception("Nothing to find. Target is empty.")
                return False
        except Exception as e:
            print("Exception has occured: ", e)
            
#UPDATE
# Method to implement the U in CRUD.
    def update(self, fromTarget, ToTarget, count):
    ###########################################################
    #This Section got a complete overhaul.
    ###########################################################
        if fromTarget is not None:
        #Instance 1
            if count == 1:
                update_result = self.database.animals.update(fromTarget, toTarget)
                print("Success!")
                print(update_result)
                return True
        #Instance 2
            elif count == 2:
                update_result = self.database.animals.update(fromTarget, toTarget)
                print("Success!")
                print(update_result)
                return True
        #Instance 0        
            else:
                print("Count not recognized - try again.")
                return False
        else:
            #lets the user know there was a problem
            raise Exception("Nothing to update, because at least one of the target parameters is empty")
            return False           
#DELETE
# Method to implement the D in CRUD
    def delete(self, target, count):
    ###########################################################
    #This Section got a complete overhaul.
    ###########################################################
        if target is not None:
        #Instance 1
            if count == 1:
                try:
                    delete_result = self.database.animals.delete_one(target)
                    print("Success!")
                    print(delete_result)
                    return True
                except Exception as e1:
                    print("An exception has occurred in instance 1:", e1)
        #Instance 2
            elif count == 2:
                try:
                    delete_result = self.database.animals.delete_many(target)
                    print("Success!")
                    print(delete_result)
                    return True
                except Exception as e2:
                    print("An exception has occurred in instance 2: ", e2)
                    return False
        #Instance 0  
            else:
                print("Count not recognized - try again.")
                return False
        else:
            #lets the user know there was a problem
            raise Exception("Nothing to delete, because the target parameter is empty")
            return False        
