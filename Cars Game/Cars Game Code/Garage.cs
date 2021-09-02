using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class Garage : MonoBehaviour
{
    public GameObject Buy;
    public GameObject InfoMessage;
    public GameObject carPrefab;
    public static GameObject carSelected;
    private GameObject saved;
    private float timeRemaining = 0.5f;
    private bool buttonPressed = false;
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
        SceneManager.LoadScene("Menu", LoadSceneMode.Additive);
        GameObject.Find("GarageRoot2").SetActive(false);
    }
}
