package cn.luozhanming.player

class MingPlayer {


    companion object{
        init {
            System.loadLibrary("native-lib")
        }
    }

    fun setDataSource(source: String){
        setDataSourceNative(source)
    }

    fun prepare(){
        prepareNative()
    }

    private external fun setDataSourceNative(source:String)
    private external fun prepareNative();
}