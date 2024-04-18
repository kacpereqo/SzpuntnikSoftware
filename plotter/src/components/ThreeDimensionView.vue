<template>
  <Renderer shadow width="800" height="800">
    <Camera :position="{ z: 50 }" />
    <Scene background="#fff">
      <PointLight
        :position="{ y: 50, z: 50 }"
        cast-shadow
        color="#fff"
        intensity="1"
        :shadow-map-size="{ width: 512, height: 512 }"
      />
      <Box :size="10" :rotation="{ x: x, z: y, y: z }" cast-shadow>
        <LambertMaterial color="green" />
      </Box>
      <Plane :width="100" :height="100" :position="{ z: -20 }" receive-shadow>
        <LambertMaterial />
      </Plane>
    </Scene>
  </Renderer>
</template>

<script setup lang="ts">
import { Box, Camera, LambertMaterial, PointLight, Renderer, Scene } from 'troisjs'
import { ref } from 'vue'

const x = ref(0)
const y = ref(0)
const z = ref(0)

const ws = new WebSocket('ws://127.0.0.1:8000/ws')

ws.onopen = () => {
  console.log('Connected')
}

ws.onmessage = (event) => {
  const data = event.data.split(',').map(Number)
  x.value = (data[0] * Math.PI) / 180
  y.value = (data[1] * Math.PI) / 180
  z.value = (data[2] * Math.PI) / 180
}
</script>

<style scoped></style>
