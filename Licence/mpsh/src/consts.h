/**
 * @file consts.h
 * @author Félix Desmaretz
 * @brief Defines all constants.
 * @version 0.1
 * @date 2019-01-03
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef CONSTS_H
#define CONSTS_H

#define BUFFER_SIZE 1024
#define SPLITER_TOKEN " \n\r\t\a"

/**
 * @brief String buffer size.
 */
#define BUFFER 512

/**
 * @brief Default umask
 */
#define DEFAULT_UMASK 022

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/**
 * @brief Boolean false.
 */
#define FALSE 0
/**
 * @brief Boolean true.
 */
#define TRUE !FALSE

/**
 * @brief ascii art string of author name (Louis).
 */
#define ascii_art_name_louis \
	"       ,gggg,\n\
      d8\" \"8I\n\
      88  ,dP\n\
   8888888P\"                              gg\n\
      88                                  \"\"\n\
      88          ,ggggg,    gg      gg   gg     ,g,\n\
 ,aa,_88         dP\"  \"Y8ggg I8      8I   88    ,8'8,\n\
dP\" \"88P        i8'    ,8I   I8,    ,8I   88   ,8'  Yb\n\
Yb,_,d88b,,_   ,d8,   ,d8'  ,d8b,  ,d8b,_,88,_,8'_   8)\n\
 \"Y8P\"  \"Y88888P\"Y8888P\"    8P'\"Y88P\"`Y88P\"\"Y8P' \"YY8P8P\n"

/**
 * @brief ascii art string of author name (Louis).
 */
#define ascii_art_name_felix \
	" ,gggggggggggggg\n\
dP\"\"\"\"\"\"88\"\"\"\"\"\"        ,dPYb,\n\
Yb,_    88              IP'`Yb\n\
 `\"\"    88              I8  8I  gg\n\
     ggg88gggg          I8  8'  \"\"\n\
        88   8  ,ggg,   I8 dP   gg      ,gg,   ,gg\n\
        88     i8\" \"8i  I8dP    88     d8\"\"8b,dP\"\n\
  gg,   88     I8, ,8I  I8P     88    dP   ,88\"\n\
   \"Yb,,8P     `YbadP' ,d8b,_ _,88,_,dP  ,dP\"Y8,\n\
     \"Y8P'    888P\"Y8888P'\"Y888P\"\"Y88\"  dP\"   \"Y88"

#endif // CONSTS_H