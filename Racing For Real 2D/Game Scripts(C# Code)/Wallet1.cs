using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
public class Wallet1 : MonoBehaviour
{
    public static int money;
    TextMeshProUGUI moneyText;
    // Start is called before the first frame update
    void Start()
    {
        moneyText = GetComponent<TextMeshProUGUI>();
        money = PlayerPrefs.GetInt("starting money");
        moneyText.text = money + "$";
    }

    // Update is called once per frame
    void Update()
    {
        if(PauseManager.raceWon)
        {
            money = PlayerPrefs.GetInt("money after race win");
            PauseManager.raceWon = false;
        }
        if(PauseManager.raceLost)
        {
            money = PlayerPrefs.GetInt("money after race lost");
            PauseManager.raceLost = false;
        }
        moneyText.text = money + "$";
    }
}
