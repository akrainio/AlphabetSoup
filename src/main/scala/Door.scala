class Door(val charType: Char) {

  val maxSlide = 9
  val maxStock = 8
  var slide: Int = maxSlide
  var stock: Int = maxStock

  def set(value: Int): Int = {
    slide = value
    val stockChange = {
      if (slide < stock) stock - slide
      else 0
    }
    stock = stock - stockChange
    stockChange
  }

  def reset(): Unit = {
    stock = maxStock
    slide = maxSlide
  }

  def close(): Unit = {
    slide = maxSlide
  }

}