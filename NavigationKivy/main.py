#from kivy.app import App 
import kivy
from kivy.core.window import Window
from kivymd.app import MDApp
from kivy.lang import Builder 
from kivy.uix.screenmanager import ScreenManager
from kivymd.uix.screen import MDScreen
from kivy.properties import ObjectProperty
import os,string
from ctypes import *

so_file = "/Users/z0049vpu.AD001/Desktop/VisualStudioCode/C_C++/NavigationKivy/_dijkstra2.so"
cfunctions = CDLL(so_file)


from kivy.config import Config
#Config.set('graphics', 'width', '980')
#Config.set('graphics', 'height', '704')
#Config.write()

__version__ = "1.0.3"


cnt=0



#define our different Screens
class MainMenu(MDScreen):


    def cities(self, dep):
        
        global cnt 

        global via

        global deps

        global dest

        cities_dictionary = {
            0: 'Karlsruhe',
            1: 'Stuttgart',
            2: 'Mannheim',
            3: 'Pforzheim',
            4: 'Rastatt',
            5: 'Baden-Baden',
            6: 'Freiburg',
            7: 'Offenburg',
            8: 'Kehl',
            9: 'Freudenstadt',
            10: 'Reutlingen',
            11: 'Tübingen',
            12: 'Ulm',
            13: 'Lörrach',
            14: 'Konstanz'
        }

        if (cnt==2):
            screen = self.manager.get_screen('main')
            screen.ids['via'].text = "Via: "+ cities_dictionary.get(int(dep))
            cnt=3
            via=str(dep)
            
        if (cnt==1):
            screen = self.manager.get_screen('main')
            screen.ids['destination'].text = "Destination: "+ cities_dictionary.get(int(dep))
            cnt=2
            dest=str(dep)

        if (cnt==0):
            screen = self.manager.get_screen('main')
            screen.ids['departure'].text = "Departure: "+ cities_dictionary.get(int(dep))
            cnt=1
            deps=str(dep)

    def clear(self):

        global cnt 
        screen = self.manager.get_screen('main')
        screen.ids['via'].text = "Via: "
        screen.ids['destination'].text = "Destination: "
        screen.ids['departure'].text = "Departure: "
        cnt=0

    def print(self):

        global cnt 

        if (cnt==3):
            cfunctions.dijkstra3(int(deps),int(via),int(dest))
            cnt=0
        if (cnt==2):
            cfunctions.dijkstra2(int(deps),int(dest))
            cnt=0
        if (cnt==1):
            cnt=0

        screen = self.manager.get_screen('main')
        screen.ids['via'].text = "Via: "
        screen.ids['destination'].text = "Destination: "
        screen.ids['departure'].text = "Departure: "
        cnt=0

    
    def clear(self):

        global cnt 
        screen = self.manager.get_screen('main')
        screen.ids['via'].text = "Via: "
        screen.ids['destination'].text = "Destination: "
        screen.ids['departure'].text = "Departure: "
        cnt=0
       
#define our WindowManager class which is responsible in switching screens
class WindowManager(ScreenManager):
    pass      

#designate our .kv design file
kv= Builder.load_file('Navi.kv')


class AwesomeApp(MDApp):

    def build(self):

        #Window.clearcolor=(1,1,1,1)
     
        return WindowManager()


if __name__ =='__main__':
    AwesomeApp().run()
