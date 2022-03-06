## Capstone Jacob Mousseau

I want to start off by saying I recently had to do a deep clean of my computer so a lot of my files and artifacts from previous classes were moved or I was unable to find them, so my options were mostly limited to stuff I have in other github repositories.



##CATEGORY: Software Engineering / Design

###[CS360 Phone Inventory Project]

The design of this application is not all that great, while clean, it is very bare bones and lacks much substance, meaning it has no real way of being user engaging and allowing them to understand what they are working with. I want to make it cleaner and more consistent between elements, as well as fixing the landscape views of this project, as they do not look quite right, provided below are the portrait designs, and a simple chart for how I want to make them more consistent.

[!All Three main windows, portrait mode](Design)

While one of the main goals was to design a working database for inventory manage on a phone, I selected this here for the design aspect due to the ability to design a clean looking application that would perform those functions, but I am still not entirely happy with this project as a whole, and figured I could potentially make it look nicer. Although, if I find a way to access my older work from other classes, I may want to change this for changing another projects design. 
    
    
##CATEGORY: Algorithms and Data Structures
    
[SQL INJECTION FILE](https://github.com/JakeNStuff/JakeNStuff.Github.io/blob/main/SQLInjection.cpp)
    
The SQL Injection practice code is from CS 405's second module if I recall correctly. The purpose of this assignment was to familiarize ourselves with how sql injections work by testing various injections and how they would 'infect' a database query. There was one section of TODO work while a good chunk of this program we were not supposed to touch. We were supposed to force the method to fail if there was a SQL injection suspected but we had to make sure it was not overly specific, as something like 1=1 would not be able to stop the flow. My code for the section in question is shown here:
    
```
// TODO: Fix this method to fail and display an error if there is a suspected SQL Injection
    //  NOTE: You cannot just flag 1=1 as an error, since 2=2 will work just as well. You need
    //  something more generic
    int pos = find_match_position(sql.c_str());
    if (pos >= 0)
        //I couldn't really think of an all that better way to do this part of the code after thinkering with it. 
        std::cout << "\nTERMINATE SQL INJECTION ATTEMPT!\n";
    char temp[100]; //Lower character number just based on length of the phrases used.
    int x = 0;
    for (x = 0; x < pos; x++)
        temp[x] = sql.c_str()[x];
    temp[x] = '\0';

    // clear any prior results
    records.clear();

  char* error_message;
  if(sqlite3_exec(db, sql.c_str(), callback, &records, &error_message) != SQLITE_OK)
  {
    std::cout << "Data failed to be queried from USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }

  return true;
}
```
                                                                                                     
In order to enhance this code and my understanding, I would want to think of other situations where potential sql injections could happen based on the input information, and how to stop them, this would require tinkering with the sections we were not supposed to touch during the assignment. 

                                                                                                     
                                                                                                     
##CATEGORY: Databases

###[CS360 Phone Inventory Project- Saving Information]

As mentioned previously about missing files that I needed, I currently can not show this application in it's 'functional' state, and firstly, it didn't fully work, as items put into the inventory database could not actually be saved or edited, which is the first thing I would need to fix in order to enhance this projects work, make the database save the information, because the test logins work but the information is not saved based on those logins yet. Essentially, this is a shell for a potential database design. 

```
Once a user is logged in, they should be able to view their companies inventory, stock, and other information.

At the bottom there is two buttons, new, and modify entry buttons.

Hitting new takes them to the entry creation window where they can add in the name, stock, and notes.

Ideally, modify would use a similar page to modify already existing information.

Hitting Add Entry should add the information, and go back should return you to the previous window, while undo should delete the most recent addition.
```

Missing a lot of my files while beginning this capstone has really made me freak out for what I should put here, if there is a way to access previous classes work through brightspace outside of the most recent classes, I would love to be able to access my other content. 

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/JakeNStuff/JakeNStuff.Github.io/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
