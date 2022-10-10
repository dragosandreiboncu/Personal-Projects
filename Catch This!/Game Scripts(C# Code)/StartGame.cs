using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StartGame : MonoBehaviour
{
    float intro_countdown;
    private bool isConnected = false;
    [SerializeField] private string versionName = "0.1";

    void Start()
    {
        intro_countdown = 2f;
    }

    // Update is called once per frame
    void Update()
    {
        if (intro_countdown <= 0 && !isConnected)
        {
            PhotonNetwork.ConnectUsingSettings(versionName);
            isConnected = true;
        }
        else
            intro_countdown -= Time.deltaTime;
    }

    private void OnConnectedToMaster()
    {
        PhotonNetwork.JoinLobby(TypedLobby.Default);
        PhotonNetwork.playerName = "";
        Debug.Log("Connected to master");
        GameObject.FindGameObjectWithTag("Music").GetComponent<PlayMenuMusic>().PlayMusic();
        SceneManager.LoadScene(1);
    }

    private void OnDisconnected()
    {
        //daca mesaj eroare daca nu ma pot conecta la sv (ex nu am net)
    }
}
