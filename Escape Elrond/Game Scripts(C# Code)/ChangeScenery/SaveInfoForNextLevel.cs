using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SaveInfoForNextLevel : MonoBehaviour
{
    // Stats to be saved
    public string nextDoor = null;
    public int playerHealth = -1;
    public int playerExperience = -1;
    public int playerLevel = -1;
    public int playerCoins = -1;
    public int playerMaxHealth = -1;
    public int playerAttack = 10;
    public bool gameOver = false;
    void Awake()
    {
        DontDestroyOnLoad(this.gameObject);
    }
}
