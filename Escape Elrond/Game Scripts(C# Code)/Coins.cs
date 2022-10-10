using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Coins : MonoBehaviour
{
	public Text coin;
    public GameObject coinsUI;

	public void SetCoin(int money)
	{
		coin.text = money.ToString();
	}

    public void SetA(bool val)
    {
        coinsUI.SetActive(val);
    }

}
