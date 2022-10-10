using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FeeCollecter : MonoBehaviour
{
    public GameObject LoadingScreen;
    public GameObject RaceSelectorMenu;
    public GameObject InfoMessage;
    public float trackFee;

    private float timeRemaining = 0.5f;
    private bool buttonPressed = false;
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Return))
            CollectFee();
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
    public void CollectFee()
    {
        if(!buttonPressed)
        {
            buttonPressed = true;
            timeRemaining = 0.5f;
            if(Wallet2.money >= trackFee)
            {
                Wallet2.money -= (int)trackFee;
                PlayerPrefs.SetInt("money after track select", Wallet2.money);
                RaceSelectorMenu.SetActive(false);
                LoadingScreen.SetActive(true);
            }
            else
            {
                InfoMessage.SetActive(true);
            }
        }
    }
}
