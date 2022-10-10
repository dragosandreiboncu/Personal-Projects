using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class SetPlayerStats : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        // Find Object with saved data
        GameObject sceneManager = GameObject.Find("SceneManagerDontDestroy(Clone)");
        GameObject skillTree = GameObject.Find("SkillTree");
        var saveInfo = sceneManager.GetComponent<SaveInfoForNextLevel>();
        if (saveInfo.playerHealth != -1)
        {
                // Find the script with player stats and change the stats
                var playerStats = GetComponent<PlayerStats>();
                playerStats.life = saveInfo.playerHealth;
                Debug.Log("------------" + playerStats.life);
                Debug.Log(SceneManager.GetActiveScene().name);
                playerStats.experience = saveInfo.playerExperience;
                playerStats.level = saveInfo.playerLevel;
                playerStats.coins = saveInfo.playerCoins;
                playerStats.maxHealth = saveInfo.playerMaxHealth;
                playerStats.attack = saveInfo.playerAttack;
                playerStats.healthBar.SetMaxHealth(saveInfo.playerMaxHealth);
                playerStats.healthBar.SetHealth(saveInfo.playerHealth);
                playerStats.progressBar.slider.maxValue = 100 * saveInfo.playerLevel;
                playerStats.progressBar.CurrentValue = saveInfo.playerExperience;
                // ***Change UI max health (maybe add current health too) -> if needed later
        }
    }
}
