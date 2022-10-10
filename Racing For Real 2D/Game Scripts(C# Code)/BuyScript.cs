using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BuyScript : MonoBehaviour
{
    public GameObject InfoMessage1;
    public GameObject InfoMessage2;
    public GameObject BuyButton;
    public GameObject UpgradeButton;
    public GameObject Price;
    public float carPrice;

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
                InfoMessage2.SetActive(false);
                buttonPressed = false;
            }
        }
    }
    public void Buy()
    {
        if(!buttonPressed)
        {
            buttonPressed = true;
            timeRemaining = 0.5f;
            if(Wallet1.money >= carPrice)
            {
                Wallet1.money -= (int)carPrice;
                BuyButton.SetActive(false);
                UpgradeButton.SetActive(true);
                Price.SetActive(false);
                InfoMessage2.SetActive(true);
            }
            else
            {
                InfoMessage1.SetActive(true);
            }
        }
    }
}
