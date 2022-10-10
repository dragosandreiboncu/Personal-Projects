using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
public class Wallet2 : MonoBehaviour
{
    public static int money;
    TextMeshProUGUI moneyText;
    // Start is called before the first frame update
    void Start()
    {
        moneyText = GetComponent<TextMeshProUGUI>();
        money = PlayerPrefs.GetInt("money after garage");
        moneyText.text = money + "$";
    }

    // Update is called once per frame
    void Update()
    {
        moneyText.text = money + "$";
    }
}

