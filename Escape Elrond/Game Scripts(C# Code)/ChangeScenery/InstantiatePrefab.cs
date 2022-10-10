using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstantiatePrefab : MonoBehaviour
{
    public Transform sceneManager;
    public Transform skillTree;
    private void Awake()
    {
        if (GameObject.Find("SceneManagerDontDestroy(Clone)") == null)
        {
            Instantiate(sceneManager, new Vector3(0, 0, 0), Quaternion.identity);
        }

        if (GameObject.Find("Skill_Tree_Canvas(Clone)") == null)
        {
            Instantiate(skillTree, new Vector3(0, 0, 0), Quaternion.identity);
        }
    }

}
