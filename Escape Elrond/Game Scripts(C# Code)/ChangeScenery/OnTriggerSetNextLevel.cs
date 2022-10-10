using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class OnTriggerSetNextLevel : MonoBehaviour
{
    private bool isTouched = false;
    public int nextLevel = -1;
    public string nextDoor = null;
    private GameObject toolTip = null;
    void Awake()
    {
        // Find the text tooltip
        Transform toolTipTranform = gameObject.transform.Find("ToolTip");
        if (toolTipTranform != null)
        {
            toolTip = toolTipTranform.gameObject;
            toolTip.SetActive(false);
        }
        else
        {
            Debug.Log("ToolTip not found for door " + gameObject.name);
        }
    }
    void OnTriggerEnter2D(Collider2D col)
    {
        // Door has been touched
        if (col.gameObject.tag == "Player")
        {
            isTouched = true;
            if (toolTip != null)
            {
                toolTip.SetActive(true);
            }
        }
    }

    void OnTriggerExit2D(Collider2D col)
    {

        // Door isn't touched anymore
        if (col.gameObject.tag == "Player")
        {
            isTouched = false;
            if (toolTip != null)
            {
                toolTip.SetActive(false);
            }
        }
    }

    void Update()
    {
        if (isTouched && Input.GetKey(KeyCode.E))
        {
            if (nextLevel == -1 || nextDoor == null)
            {
                Debug.LogWarning("Level or Door not setup");
                return;
            }

            // Find player stats and script with saved player stats
            GameObject sceneManager = GameObject.Find("SceneManagerDontDestroy(Clone)");
            GameObject player = GameObject.Find("Player");
            var saveInfo = sceneManager.GetComponent<SaveInfoForNextLevel>();
            var playerStats = player.GetComponent<PlayerStats>();

            // Save the player stats
            saveInfo.nextDoor = nextDoor;
            saveInfo.playerHealth = playerStats.life;
            saveInfo.playerExperience = playerStats.experience;
            saveInfo.playerLevel = playerStats.level;
            saveInfo.playerCoins = playerStats.coins;
            saveInfo.playerMaxHealth = playerStats.maxHealth;
            saveInfo.playerAttack = playerStats.attack;
            SceneManager.LoadScene(nextLevel);
        }
    }
}
