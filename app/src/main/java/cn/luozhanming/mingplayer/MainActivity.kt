package cn.luozhanming.mingplayer

import android.app.Activity
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.widget.Button
import cn.luozhanming.player.MingPlayer

class MainActivity : AppCompatActivity() {

    private var player:MingPlayer? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var button = findViewById<Button>(R.id.play)
        button.setOnClickListener {
            player = MingPlayer()
            player?.setDataSource("${Environment.getExternalStorageDirectory()}/demo.mp4")
            player?.prepare()
        }

    }
}