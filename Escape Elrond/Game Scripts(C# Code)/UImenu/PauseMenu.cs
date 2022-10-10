using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{

    public bool GameIsPaused = false;
    public static bool IsInOptions = false;
    public GameObject pauseMenuUI;
    public GameObject optionsMenuUI;

    // Update is called once per frame
    void Update()
    {
       if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (GameIsPaused)
            {
                if (IsInOptions)
                {
                    GoToPauseMenu();
                }
                else
                {
                    Resume();
                }
            } else
            {
                Pause();
            }
        }
    }

    public void Resume ()
    {
        pauseMenuUI.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
    }

    void Pause()
    {
        pauseMenuUI.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
    }

    public void BackToMenu()
    {
        Destroy(GameObject.Find("Skill_Tree_Canvas(Clone)"));
        Destroy(GameObject.Find("SceneManagerDontDestroy(Clone)"));
        Time.timeScale = 1f;
        SceneManager.LoadScene("MainMenu");
        Time.timeScale = 1f;
    }

    public void Options()
    {
        optionsMenuUI.SetActive(true);
        pauseMenuUI.SetActive(false);
        Time.timeScale = 0f;
        GameIsPaused = true;
        IsInOptions = true;
    }

    public void GoToPauseMenu()
    {
        optionsMenuUI.SetActive(false);
        pauseMenuUI.SetActive(true);
        GameIsPaused = true;
        IsInOptions = false;
    }

    public void PlayAgain()
    {
        GameObject.Find("Skill_Tree_Canvas(Clone)").SetActive(false);
        GameObject sceneManager = GameObject.Find("SceneManagerDontDestroy(Clone)");
        var saveInfo = sceneManager.GetComponent<SaveInfoForNextLevel>();
        saveInfo.playerHealth = 100;
        saveInfo.playerExperience = 0;
        saveInfo.playerLevel = 1;
        saveInfo.playerCoins = 0;
        saveInfo.playerMaxHealth = 100;
        saveInfo.playerAttack = 10;
        Time.timeScale = 1f;
        SceneManager.LoadScene("Room_0");
        Time.timeScale = 1f;
    }

    public void DeathTime()
    {
        Time.timeScale = 0f;
    }
}
