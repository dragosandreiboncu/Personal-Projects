using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Text;
using UnityEngine.UI;
public class Garage : MonoBehaviour
{
    public GameObject Buy;
    public GameObject InfoMessage;
    public GameObject carPrefab;
    private GameObject cars;
    public static GameObject carSelected;
    private GameObject mainMenu;
    TextReader tr;
    TextWriter tw;
    private string saved;
    private float timeRemaining = 0.5f;
    private bool buttonPressed = false;
    void Start()
    {
        mainMenu = GameObject.Find("MainMenuRoot1");
        GameObject mainMenu2 = mainMenu.transform.Find("MainMenuRoot2").gameObject;
        mainMenu = mainMenu2.transform.Find("Menu Canvas").gameObject.transform.Find("Main Menu").gameObject;
        mainMenu.GetComponent<MenuManager>().CheckSave();
        if(mainMenu.GetComponent<MenuManager>().continueData != null)
        {
            cars = GameObject.Find("Cars").gameObject;
            for(int i = 1; i <= 10; i++)
            {
                string carName = "Car" + i;
                GameObject car = cars.transform.Find(carName).gameObject;
                if(mainMenu.GetComponent<MenuManager>().continueData[i*2-1] == 1)
                {
                    car.transform.Find("BuyButton").gameObject.SetActive(false);
                    car.transform.Find("UpgradeButton").gameObject.SetActive(true);
                    car.transform.Find("Infos").gameObject.transform.Find("Price").gameObject.SetActive(false);
                    car.transform.Find("BuySucces").gameObject.SetActive(true);
                }
                if(mainMenu.GetComponent<MenuManager>().continueData[i*2] == 1)
                {
                    car.transform.Find("Infos").gameObject.transform.Find("Slider").gameObject.GetComponent<Slider>().value = 100;
                    car.transform.Find("Infos").gameObject.transform.Find("Slider (1)").gameObject.GetComponent<Slider>().value = 100;
                    car.transform.Find("Infos").gameObject.transform.Find("Slider (2)").gameObject.GetComponent<Slider>().value = 100;
                    car.transform.Find("Infos").gameObject.transform.Find("Slider (3)").gameObject.GetComponent<Slider>().value = 100;
                    GameObject.Find("GarageRoot1").gameObject.transform.Find(carName).gameObject.GetComponent<CarScript>().Top_Speed = 310f;
                    GameObject.Find("GarageRoot1").gameObject.transform.Find(carName).gameObject.GetComponent<CarScript>().Acceleration = 52f;
                    GameObject.Find("GarageRoot1").gameObject.transform.Find(carName).gameObject.GetComponent<CarScript>().Brake_Force = 15f;
                    GameObject.Find("GarageRoot1").gameObject.transform.Find(carName).gameObject.GetComponent<CarScript>().Handling = 80f;
                    car.transform.Find("UpgradeButton").gameObject.SetActive(false);
                }
            }
        }

    }
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Return))
        {
            if(Buy.activeSelf)
                Buy.GetComponent<BuyScript>().Buy();
            else
                Select();
        }
        if(Input.GetKeyDown(KeyCode.Escape))
            Back();
        if(buttonPressed)
        {
            if (timeRemaining > 0)
                timeRemaining -= Time.deltaTime;
            else
            {
                InfoMessage.SetActive(false);
                buttonPressed = false;
            }
        }
    }
    public void Select()
    {
        if(!buttonPressed)
        {
            buttonPressed = true;
            timeRemaining = 0.5f;
            if(!Buy.activeSelf)
            {
                PlayerPrefs.SetInt("money after garage", Wallet1.money);
                carSelected = carPrefab;
                SceneManager.LoadScene("Races", LoadSceneMode.Additive);
                GameObject.Find("GarageRoot2").SetActive(false);
            }
            else
            {
                InfoMessage.SetActive(true);
            }
        }
    }
    public void Back()
    {
        mainMenu = GameObject.Find("MainMenuRoot1");
        GameObject mainMenu2 = mainMenu.transform.Find("MainMenuRoot2").gameObject;
        mainMenu2.SetActive(true);
        mainMenu = mainMenu2.transform.Find("Menu Canvas").gameObject.transform.Find("Main Menu").gameObject;
        mainMenu.GetComponent<MenuManager>().CheckSave();
        SceneManager.UnloadSceneAsync("Garage");
    }
    public void Save()
    {
        tw = new StreamWriter("Save.txt");
        tw.WriteLine("1");
        tw.WriteLine(Wallet1.money);
        cars = GameObject.Find("Cars");
        for(int i = 1; i <= 10; i++)
        {
            string carName = "Car" + i;
            GameObject car = cars.transform.Find(carName).gameObject;
            if(!car.transform.Find("BuyButton").gameObject.activeSelf)
            {
                tw.WriteLine("1");
                if(!car.transform.Find("UpgradeButton").gameObject.activeSelf)
                    tw.WriteLine("1");
                else
                    tw.WriteLine("0");
            }
            else
            {
                tw.WriteLine("0");
                tw.WriteLine("0");
            }
        }

        tw.Close();
    }
}
