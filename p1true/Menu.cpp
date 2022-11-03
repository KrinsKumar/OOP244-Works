#include <iostream>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds {

   MenuItem::MenuItem() {
      m_valid = false;
      strcpy(m_item, "");
   }

   MenuItem::MenuItem(const char item[]) {
      m_valid = false;
      strcpy(m_item, "");
      if (item != NULL) {
         strcpy(m_item, item);   // copies the arguement in the class
         m_valid = true;
      }
   }

   std::ostream& MenuItem::display(std::ostream& ost) const {
      if (m_valid) {
         ost << m_item << endl;
      }
      return ost;
   }

   MenuItem& MenuItem::operator=(const MenuItem& rightMenuItem) {
      MenuItem temp;
      return temp;   // returns a temp invalid instance of the class
   }
 
 //======================================================================================

   Menu::Menu() {
      m_indentation = 0;
      m_totalItems = 0;
      strcpy(m_title, "");
      m_valid = false;
   }

   Menu::Menu(const char title[], int indentation) {
      m_indentation = indentation;
      m_totalItems = 0;
      strcpy(m_title, "");
      m_valid = false;
      if (title != NULL) {
         strcpy(m_title, title);
         m_valid = true;
      }
   }

   Menu::operator bool() const {
      return m_valid;
   }

   Menu::operator int() const {
      return run();
   }

   Menu& Menu::operator=(const Menu& rightMenu)  {
      Menu temp;
      return temp;   // returns a temp invalid instance of the class
   }

   Menu& Menu::operator=(const char title[]) {
      if (title != NULL) {
         strcpy(m_title, title);
         m_valid = true;
      }
      else {
         strcpy(m_title, "");
         m_valid = true;
      }
      return *this;
   }

   Menu& Menu::operator<<(const char title[]) {
      add(title);
      return *this;
   }

   bool Menu::isEmpty() const{
      return !m_valid;
   }

   std::ostream& Menu::display(std::ostream& ost) const{
      if (m_valid) {
         if (m_totalItems == 0) {
            ost << "No Items to display!" << endl;
         }
         else {
            ost << m_title << endl;
            for (int i = 0; i < m_totalItems; i++) {
               ost << (i+1) << "- ";
               m_menuItems[i].display() << endl;
            }
            ost << "> ";
         }
      }
      else {
         ost << "Invalid Menu!" << endl;
      }
      return ost;
   }

   void Menu::add(const char item[]) {
      if (m_valid) {
         if (item != NULL) {
            if (m_totalItems < MAX_NO_OF_ITEMS) {
               m_menuItems[m_totalItems] = item;
               m_totalItems++;
            }
         }
         else {
            m_valid = false;
         }
      }
   }

   int Menu::run() const {
      int userResponse;
      if (m_totalItems == 0) {
         userResponse = 0;
      } else {
         display();
         cin >> userResponse;
         do {
            while (cin.fail()) {
               cout << "Invalid Integer, try again: ";
               cin.clear();
               cin.ignore(1000, '\n');
               cin >> userResponse;
            }
            if (userResponse > m_totalItems || userResponse < 1) {
               cout << "Invalid selection, try again: ";
            }
         } while (userResponse > m_totalItems || userResponse < 1);
      }
      return userResponse;
   }

   void Menu::clear() {
      for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
         MenuItem temp;
         m_menuItems[i] = temp;
      }
   }


}