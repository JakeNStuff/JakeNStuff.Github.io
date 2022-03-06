## Welcome to GitHub Pages

You can use the [editor on GitHub](https://github.com/JakeNStuff/JakeNStuff.Github.io/edit/main/index.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).
'''
I want to start off by saying I recently had to do a deep clean of my computer so a lot of my files and artifacts from previous classes were moved or I was unable to find them, so my options were mostly limited to stuff I have in other github repositories.
'''
##CATEGORY: Software Engineering / Design
###<file>

##CATEGORY: Algorithms and Data Structures
###[<SQL INJECTION FILE>](https://github.com/JakeNStuff/JakeNStuff.Github.io/blob/main/SQLInjection.cpp)
The SQL Injection practice code is from CS 405's second module if I recall correctly. The purpose of this assignment was to familiarize ourselves with how sql injections work by testing various injections and how they would 'infect' a database query. There was one section of TODO work while a good chunk of this program we were not supposed to touch. We were supposed to force the method to fail if there was a SQL injection suspected but we had to make sure it was not overly specific, as something like 1=1 would not be able to stop the flow. My code for the section in question is shown here:
'''
'// TODO: Fix this method to fail and display an error if there is a suspected SQL Injection
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
}'
'''
In order to enhance this code and my understanding, I would want to think of other situations where potential sql injections could happen based on the input information, and how to stop them, this would require tinkering with the sections we were not supposed to touch during the assignment. 



### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/JakeNStuff/JakeNStuff.Github.io/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
