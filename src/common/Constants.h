/*! ---------------------------------------------------------------
 * \file   Constants.h
 * \brief  Useful constants
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define MAX_STRING_SIZE          255

#define BESTALLOC_TITLE          "Best Allocation Analyzer"
#define STATUS_LABEL             "Status:"

#define EMPLOYEES_LABEL          "Employees"
#define SKILLS_LABEL             "Skills"

#define FILE_MENU_LABEL          "&File"
#define SAVE_ACTION_MENU_LABEL   "&Save"
#define LOAD_ACTION_MENU_LABEL   "&Load"

#define EDIT_MENU_LABEL          "&Edit"
#define ADD_OBJECT_MENU_LABEL    "Add &object"
#define ADD_EDGE_MENU_LABEL      "Add ed&ge"
#define ADD_TEMPLATE_MENU_LABEL  "Add &template"
#define CHANGE_OBJECT_MENU_LABEL "&Change object"
#define DELETE_OBJECT_MENU_LABEL "&Delete object"
#define CHANGE_MENU_LABEL        "&Edit"
#define DELETE_MENU_LABEL        "&Delete"

#define TOOLS_MENU_LABEL                  "&Tools"
#define GENERATE_REPORT_ACTION_MENU_LABEL "&Generate report"

#define HELP_MENU_LABEL         "&Help"

#define COMPUTE_LABEL           "Compute"
#define ADD_OBJECT_LABEL        "Add object"
#define ADD_EDGE_LABEL          "Add edge"
#define CHANGE_OBJECT_LABEL     "Change object"
#define EDIT_NODE_LABEL         "Edit node"
#define GRAPH_NODE_NAME_LABEL   "Name: "
#define GRAPH_NODE_TYPE_LABEL   "Type: "
#define GRAPH_NODE_IMAGE_LABEL  "Image: "
#define GRAPH_NODE_WEIGHT_LABEL  "Weight: "

#define GRAPH_EMPLOYEE_TYPE_LABEL "Employee"
#define GRAPH_SKILL_TYPE_LABEL    "Skill"
#define GRAPH_PATTERN_TYPE_LABEL  "Pattern"
#define GRAPH_EDGE_TYPE_LABEL     "Edge"
#define RESET_GRAPH_LABEL         "Reset"

#define CONFIRM_LABEL        "OK"
#define CANCEL_LABEL         "Cancel"
#define DELETE_LABEL         "Delete"
#define DELETE_OBJECT_LABEL  "Delete object"
#define SELECT_PICTURE_LABEL "Select picture"

#define TEXT_FILE_FILTER "Text file (*.txt)"
#define CSV_FILE_FILTER  "Table csv (*.csv)"
#define XML_FILE_FILTER  "XML file (*.xml)"

#define CSV_SEPARATOR ","

#define WARNING_TITLE "Warning"
#define ERROR_TITLE "Error"

#define CALC_WARNING_TEXT "Cannot calculate best allocation for given graph"
#define CALC_WARNING_INFO "1) The number of vertices in different parts should be the same;\n2) Each vertex must be connected with another one;"

#define CONFIRM_DELETION_TITLE "Confirm deletion"
#define CONFIRM_DELETION_TEXT  "Are you really want to this node?"
#define CONFIRM_SKILL_DELETION_TEXT  "Are you really want to delete skill "
#define CONFIRM_EMPLOYEE_DELETION_TEXT  "Are you really want to delete employee "

#define ADD_EMPLOYEE_ERROR_TEXT "Cannot add employee"
#define ADD_EMPLOYEE_ERROR_INFO "Employee already exists, try to change name"

#define ADD_SKILL_ERROR_TEXT "Cannot add skill"
#define ADD_SKILL_ERROR_INFO "Skill already exists, try to change name"

#define ADD_EDGE_ERROR_TEXT "Cannot add edge"
#define ADD_EDGE_ERROR_INFO "Edge already exists"

#define EDIT_EMPLOYEE_ERROR_TEXT "Cannot edit employee"
#define EDIT_EMPLOYEE_ERROR_INFO "Employee already exists, try to change name"

#define EDIT_SKILL_ERROR_TEXT "Cannot edit skill"
#define EDIT_SKILL_ERROR_INFO "Skill already exists, try to change name"

#define OPEN_FILE_ERROR_TEXT "Cannot open selected file"
#define OPEN_FILE_ERROR_INFO "Selected file is corrupted or has undefined format"

#define EMPLOYEE_ID    "Employee: "
#define SKILL_ID       "Skill: "
#define EDGE_ID        "Edge: "
#define EDGE_SEPARATOR " <---> "

#define MAX_NODE_NAME_LENGTH 11
#define IMAGE_PREVIEW_SIZE 300

#define GENERATE_REPORT_LABEL    "Generate report"
#define SAVE_CONFIGURATION_LABEL "Save configuration to file"
#define LOAD_CONFIGURATION_LABEL "Load configuration from file"

#define CONFIGURATION_FILE_FILTER "bestalloc files (*.bst)"

#define SAVE_CONFIG_FILE_ERROR_TEXT "Save configuration error"
#define WRITE_CONFIG_FILE_ERROR_INFO "Cannot write configuration to selected file"

#define LOAD_CONFIG_FILE_ERROR_TEXT "Load configuration error"
#define READ_CONFIG_FILE_ERROR_INFO "Cannot read configuration from selected file"
#define LOAD_CONFIG_FILE_ERROR_INFO "Selected file is corrupted or has undefined format"

#define HELP_RUNNING_WARNING_TEXT "Open help error"
#define HELP_RUNNING_WARNING_INFO "Another instance of help service has been already launched"
#define HELP_NOT_FOUND_ERROR_INFO "Help file not found"

#define DEFAULT_HELP_FILE_PATH   "helpcollection.qhc"
#define INSTALLED_HELP_FILE_PATH "/opt/bestalloc/helpcollection.qhc"

#endif // CONSTANTS_H_INCLUDED
