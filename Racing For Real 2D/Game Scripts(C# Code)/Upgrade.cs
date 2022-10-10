using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Upgrade : MonoBehaviour
{
    public GameObject InfoMessage1;
    public GameObject UpgradeButton;
    public float upgradePrice;
    public Slider Slider1;
    public Slider Slider2;
    public Slider Slider3;
    public Slider Slider4;
    public GameObject Car;

    private float timeRemaining = 0.5f;
    private bool buttonPressed = false;
    void Update()
    {
        if(buttonPressed)
        {
            if (timeRemaining > 0)
                timeRemaining -= Time.deltaTime;
            else
            {
                InfoMessage1.SetActive(false);
                buttonPressed = false;
            }
        }
    }
    public void UpgradePerf()
    {
        if(!buttonPressed)
        {
            buttonPressed = true;
            timeRemaining = 0.5f;
            if(Wallet1.money >= upgradePrice)
            {
                Wallet1.money -= (int)upgradePrice;
                Slider1.value = 100;
                Slider2.value = 100;
                Slider3.value = 100;
                Slider4.value = 100;
                Car.GetComponent<CarScript>().Top_Speed = 310f;
                Car.GetComponent<CarScript>().Acceleration = 52f;
                Car.GetComponent<CarScript>().Brake_Force = 15f;
                Car.GetComponent<CarScript>().Handling = 80f;
                UpgradeButton.SetActive(false);
            }
            else
            {
                InfoMessage1.SetActive(true);
            }
        }
    }
}
